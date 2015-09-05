
PORTNAME=	intel-gpu-tools
PORTVERSION=	1.11
CATEGORIES=	devel
MASTER_SITES=	http://xorg.freedesktop.org/releases/individual/app/

MAINTAINER=	zunknown
COMMENT=	Tools for development/testing of the i915 DRM driver

LICENSE=	MIT

USES=		tar:bzip2 gmake python:3
#PLIST_FILES=	bin/${PORTNAME}
#WRKSRC:=	${WRKDIR}/${PORTNAME}-${PORTVERSION}

BUILD_DEPENDS+=	swig2.0:${PORTSDIR}/devel/swig20
RUN_DEPENDS+=	swig2.0:${PORTSDIR}/devel/swig20
#makedepends=(swig gtk-doc xorg-util-macros )
LIB_DEPENDS=	libdrm.so:${PORTSDIR}/graphics/libdrm \
		libpciaccess.so:${PORTSDIR}/devel/libpciaccess

USE_XORG?=	x11 xv xext xrandr xf86driproto dri2proto
USE_GNOME=	cairo glib20

GNU_CONFIGURE=	yes

CONFIGURE_ARGS=	--prefix=${PREFIX} \
		--docdir=${EXAMPLESDIR} \
		--mandir=${MANPREFIX}/man \
		--without-libunwind \
		--enable-strict-compilation \
		--disable-gtk-doc --disable-gtk-doc-html

# zrj: don't annoy me
CONFIGURE_ARGS+= xorg_cv_cc_flag__pedantic=no \
		 xorg_cv_cc_flag__errwarn=no enable_overlay_xvlib=no

CFLAGS+=	-std=c99 -Wno-variadic-macros -Wno-maybe-uninitialized

.include <bsd.port.mk>
