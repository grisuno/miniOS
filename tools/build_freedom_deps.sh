#!/usr/bin/env bash
# Build the static libraries the full FreeDom GUI needs on MiniOS that the
# host distribution does not ship as archives: pixman, HarfBuzz, Cairo and a
# minimal libcurl.
#
# MiniOS runs FreeDom as one static glibc ELF (host gcc -static -no-pie, like
# DOOM and Quake 2). Most dependencies exist as host .a archives (FreeType,
# fontconfig, expat, libpng, zlib, libjpeg, libwebp, OpenSSL, lexbor). These
# four do not, or exist only with dependencies that cannot link statically
# (the distribution libcurl pulls GSSAPI, LDAP and GnuTLS), so they are built
# here from pinned upstream releases:
#
#   pixman   image backend of Cairo
#   harfbuzz text shaping, FreeType support only (no glib, no ICU)
#   cairo    image, PDF and FreeType/fontconfig backends only (no X11, no glib)
#   curl     HTTP and HTTPS over OpenSSL and zlib only; every other protocol,
#            resolver backend and auth mechanism disabled
#   dejavu   the DejaVu Sans, Sans Mono and Serif faces FreeDom's fontconfig
#            aliases resolve to (local fonts only, never fetched at runtime)
#   cacert   the Mozilla root store curl.se extracts, at the Linux-standard
#            path libcurl is configured to read (/etc/ssl/certs/
#            ca-certificates.crt on MiniFS)
#
# Every tarball is pinned by version and SHA-256; a mismatch aborts before
# anything is extracted. A package whose stamp records the same version and
# hash is skipped, so the script is idempotent and cheap to rerun.
#
# Usage:
#   tools/build_freedom_deps.sh [--prefix DIR] [--cache DIR] [--jobs N]
#
# Inputs:
#   --prefix DIR  install prefix (default: progs/freedomui/deps/prefix).
#   --cache DIR   download and build area (default: progs/freedomui/deps/cache).
#   --jobs N      parallel build jobs (default: online CPU count).
#   --help        print this help and exit.
#
# Outputs:
#   DIR/lib/{libpixman-1,libharfbuzz,libcairo,libcurl}.a, their headers under
#   DIR/include, pkg-config files under DIR/lib/pkgconfig and the font faces
#   under DIR/share/fonts/dejavu. The Makefile target freedom-deps runs this
#   script with the defaults.
#
# Failure modes:
#   Exits nonzero when a download fails, a SHA-256 does not match, a required
#   host tool (curl, meson, ninja, pkg-config, tar, sha256sum) is missing, or
#   a configure/build step fails. A failed package leaves no stamp, so the
#   next run rebuilds it from a clean tree.
set -euo pipefail

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

readonly PIXMAN_VERSION="0.44.2"
readonly PIXMAN_URL="https://cairographics.org/releases/pixman-${PIXMAN_VERSION}.tar.gz"
readonly PIXMAN_SHA256="6349061ce1a338ab6952b92194d1b0377472244208d47ff25bef86fc71973466"

readonly HARFBUZZ_VERSION="10.1.0"
readonly HARFBUZZ_URL="https://github.com/harfbuzz/harfbuzz/releases/download/${HARFBUZZ_VERSION}/harfbuzz-${HARFBUZZ_VERSION}.tar.xz"
readonly HARFBUZZ_SHA256="6ce3520f2d089a33cef0fc48321334b8e0b72141f6a763719aaaecd2779ecb82"

readonly CAIRO_VERSION="1.18.2"
readonly CAIRO_URL="https://cairographics.org/releases/cairo-${CAIRO_VERSION}.tar.xz"
readonly CAIRO_SHA256="a62b9bb42425e844cc3d6ddde043ff39dbabedd1542eba57a2eb79f85889d45a"

readonly CURL_VERSION="8.11.1"
readonly CURL_URL="https://curl.se/download/curl-${CURL_VERSION}.tar.xz"
readonly CURL_SHA256="c7ca7db48b0909743eaef34250da02c19bc61d4f1dcedd6603f109409536ab56"
# Bumped whenever the configure line below changes, so the stamp forces a
# rebuild instead of keeping a library built with the old options.
readonly CURL_CONFIG_REV="2"
readonly CURL_CA_BUNDLE="/etc/ssl/certs/ca-certificates.crt"

readonly CACERT_VERSION="2026-09-25"
readonly CACERT_URL="https://curl.se/ca/cacert-${CACERT_VERSION}.pem"
readonly CACERT_SHA256="a41b5d356aea97a529fe27e0f7316d2f9d946d75927476cf9cf1b90637d00505"

readonly DEJAVU_VERSION="2.37"
readonly DEJAVU_URL="https://github.com/dejavu-fonts/dejavu-fonts/releases/download/version_2_37/dejavu-fonts-ttf-${DEJAVU_VERSION}.tar.bz2"
readonly DEJAVU_SHA256="fa9ca4d13871dd122f61258a80d01751d603b4d3ee14095d65453b4e846e17d7"
readonly DEJAVU_FACES="DejaVuSans DejaVuSans-Bold DejaVuSans-Oblique DejaVuSansMono DejaVuSansMono-Bold DejaVuSansMono-Oblique DejaVuSerif DejaVuSerif-Bold"

readonly REQUIRED_TOOLS="curl meson ninja pkg-config tar sha256sum make"

PREFIX="${REPO_DIR}/progs/freedomui/deps/prefix"
CACHE="${REPO_DIR}/progs/freedomui/deps/cache"
JOBS="$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)"

usage() {
    sed -n '2,/^set -euo pipefail/p' "$0" | sed '$d' | sed 's/^# \?//'
}

die() {
    echo "build_freedom_deps: $*" >&2
    exit 1
}

while [ $# -gt 0 ]; do
    case "$1" in
        --prefix)  PREFIX="${2:?--prefix needs an argument}"; shift 2 ;;
        --cache)   CACHE="${2:?--cache needs an argument}"; shift 2 ;;
        --jobs)    JOBS="${2:?--jobs needs an argument}"; shift 2 ;;
        --help|-h) usage; exit 0 ;;
        *)         echo "build_freedom_deps: unknown argument: $1" >&2; usage >&2; exit 2 ;;
    esac
done

case "${JOBS}" in
    ''|*[!0-9]*) die "--jobs must be a positive integer" ;;
esac
[ "${JOBS}" -gt 0 ] || die "--jobs must be a positive integer"

for tool in ${REQUIRED_TOOLS}; do
    command -v "${tool}" >/dev/null 2>&1 || die "missing host tool: ${tool}"
done

mkdir -p "${PREFIX}" "${CACHE}"
PREFIX="$(cd "${PREFIX}" && pwd)"
CACHE="$(cd "${CACHE}" && pwd)"

export PKG_CONFIG_PATH="${PREFIX}/lib/pkgconfig${PKG_CONFIG_PATH:+:${PKG_CONFIG_PATH}}"
export CFLAGS="-O2 -fno-plt"
export CXXFLAGS="-O2 -fno-plt"

# fetch NAME URL SHA256: download into the cache once and verify the hash.
fetch() {
    local name="$1" url="$2" sha="$3"
    local file="${CACHE}/$(basename "${url}")"
    if [ ! -f "${file}" ]; then
        curl -sSfL --proto '=https' --tlsv1.2 -o "${file}.part" "${url}" \
            || die "download failed: ${url}"
        mv "${file}.part" "${file}"
    fi
    echo "${sha}  ${file}" | sha256sum -c --status - \
        || { rm -f "${file}"; die "${name}: SHA-256 mismatch for ${file}"; }
    printf '%s\n' "${file}"
}

# unpack NAME FILE: extract into a fresh source tree and print its path.
unpack() {
    local name="$1" file="$2"
    local dir="${CACHE}/src-${name}"
    rm -rf "${dir}"
    mkdir -p "${dir}"
    tar -xf "${file}" -C "${dir}" --strip-components=1
    printf '%s\n' "${dir}"
}

stamp_ok() {
    local name="$1" sha="$2"
    [ -f "${PREFIX}/.stamp-${name}" ] && [ "$(cat "${PREFIX}/.stamp-${name}")" = "${sha}" ]
}

stamp_write() {
    printf '%s' "$2" > "${PREFIX}/.stamp-$1"
}

# meson_static NAME SRC [OPTIONS...]: static release build installed to PREFIX.
meson_static() {
    local name="$1" src="$2"
    shift 2
    local build="${CACHE}/build-${name}"
    rm -rf "${build}"
    meson setup "${build}" "${src}" \
        --prefix "${PREFIX}" --libdir lib \
        --default-library=static --buildtype=release \
        -Dwrap_mode=nodownload "$@"
    ninja -C "${build}" -j "${JOBS}" install
}

build_pixman() {
    stamp_ok pixman "${PIXMAN_SHA256}" && return 0
    local src
    src="$(unpack pixman "$(fetch pixman "${PIXMAN_URL}" "${PIXMAN_SHA256}")")"
    meson_static pixman "${src}" \
        -Dtests=disabled -Ddemos=disabled -Dgtk=disabled \
        -Dlibpng=disabled -Dopenmp=disabled
    stamp_write pixman "${PIXMAN_SHA256}"
}

build_harfbuzz() {
    stamp_ok harfbuzz "${HARFBUZZ_SHA256}" && return 0
    local src
    src="$(unpack harfbuzz "$(fetch harfbuzz "${HARFBUZZ_URL}" "${HARFBUZZ_SHA256}")")"
    meson_static harfbuzz "${src}" \
        -Dfreetype=enabled -Dglib=disabled -Dgobject=disabled \
        -Dcairo=disabled -Dicu=disabled -Dgraphite2=disabled \
        -Dchafa=disabled -Dtests=disabled -Ddocs=disabled \
        -Dutilities=disabled -Dintrospection=disabled -Dbenchmark=disabled
    stamp_write harfbuzz "${HARFBUZZ_SHA256}"
}

build_cairo() {
    stamp_ok cairo "${CAIRO_SHA256}" && return 0
    local src
    src="$(unpack cairo "$(fetch cairo "${CAIRO_URL}" "${CAIRO_SHA256}")")"
    meson_static cairo "${src}" \
        -Dfreetype=enabled -Dfontconfig=enabled -Dpng=enabled -Dzlib=enabled \
        -Dxlib=disabled -Dxcb=disabled -Dglib=disabled -Dquartz=disabled \
        -Ddwrite=disabled -Dtee=disabled -Dxlib-xcb=disabled -Dspectre=disabled \
        -Dsymbol-lookup=disabled -Dtests=disabled -Dgtk_doc=false
    stamp_write cairo "${CAIRO_SHA256}"
}

build_curl() {
    stamp_ok curl "${CURL_SHA256}:${CURL_CONFIG_REV}" && return 0
    local src
    src="$(unpack curl "$(fetch curl "${CURL_URL}" "${CURL_SHA256}")")"
    (
        cd "${src}"
        ./configure --prefix="${PREFIX}" --libdir="${PREFIX}/lib" \
            --disable-shared --enable-static --with-pic \
            --with-openssl --with-zlib \
            --enable-http --disable-ftp --disable-file --disable-ldap \
            --disable-ldaps --disable-rtsp --disable-proxy-auth-ntlm \
            --disable-dict --disable-telnet --disable-tftp --disable-pop3 \
            --disable-imap --disable-smb --disable-smtp --disable-gopher \
            --disable-mqtt --disable-manual --disable-docs --disable-ntlm \
            --disable-kerberos-auth --disable-negotiate-auth \
            --disable-alt-svc --disable-hsts --disable-websockets \
            --enable-threaded-resolver --enable-ipv6 \
            --without-brotli --without-zstd --without-libpsl \
            --without-libidn2 --without-libssh2 --without-libssh \
            --without-nghttp2 --without-nghttp3 --without-ngtcp2 \
            --without-gssapi --without-librtmp --without-libgsasl \
            --with-ca-bundle="${CURL_CA_BUNDLE}" --without-ca-path
        make -j "${JOBS}"
        make install
    )
    stamp_write curl "${CURL_SHA256}:${CURL_CONFIG_REV}"
}

build_dejavu() {
    stamp_ok dejavu "${DEJAVU_SHA256}" && return 0
    local src face
    src="$(unpack dejavu "$(fetch dejavu "${DEJAVU_URL}" "${DEJAVU_SHA256}")")"
    mkdir -p "${PREFIX}/share/fonts/dejavu"
    for face in ${DEJAVU_FACES}; do
        [ -f "${src}/ttf/${face}.ttf" ] || die "dejavu: missing face ${face}"
        install -m 0644 "${src}/ttf/${face}.ttf" "${PREFIX}/share/fonts/dejavu/${face}.ttf"
    done
    stamp_write dejavu "${DEJAVU_SHA256}"
}

build_cacert() {
    stamp_ok cacert "${CACERT_SHA256}" && return 0
    local file
    file="$(fetch cacert "${CACERT_URL}" "${CACERT_SHA256}")"
    mkdir -p "${PREFIX}/share/ca"
    install -m 0644 "${file}" "${PREFIX}/share/ca/cacert.pem"
    stamp_write cacert "${CACERT_SHA256}"
}

build_pixman
build_harfbuzz
build_cairo
build_curl
build_dejavu
build_cacert
echo "build_freedom_deps: ok (${PREFIX})"
