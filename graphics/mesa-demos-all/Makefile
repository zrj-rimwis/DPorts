# DragonFly

PORTNAME=	mesa-demos-all
PORTVERSION=	8.2.0.151016
PORTREVISION=	2
CATEGORIES=	graphics

USE_GITHUB=	yes
GH_ACCOUNT=	zrj-rimwis
GH_PROJECT=	mesa-demos
GH_TAGNAME=	ae76b2a

MAINTAINER=	zrj@ef
COMMENT=	More OpenGL demos distributed with Mesa (master)

# mesa-demos also installs some of the demos, no more
#CONFLICTS_INSTALL=	mesa-demos

GNU_CONFIGURE=	yes
USES=		gmake pkgconfig tar:bzip2
USE_GL=		glew glu glut
USE_XORG=	dri2proto glproto x11 xdamage xext xfixes xi xxf86vm

CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

DATADIR=	${PREFIX}/share/mesa-demos-all

USES+=	autoreconf:build libtool
CFLAGS+= -Wno-strict-prototypes

OPTIONS_DEFINE= X11 EGL OSMESA WAYLAND ZEXTRA
OPTIONS_DEFAULT= X11 EGL OSMESA ZEXTRA

X11_DESC=	X11 demos
EGL_DESC=	EGL demos
OSMESA_DESC=	OSMESA demos
WAYLAND_DESC=	Wayland demo es2gears_wayland)
ZEXTRA_DESC=	Many extra samples, redbook, egl

CONFIGURE_ARGS+=--with-system-data-files --bindir=${PREFIX}/bin/examples/mesa

# OpenVG disable
CONFIGURE_ARGS+=--disable-vg --disable-freetype2

CONFIGURE_ARGS+=--disable-gles1 --disable-rbug

.include <bsd.port.pre.mk>

.if ${PORT_OPTIONS:MOSMESA}
LIB_DEPENDS+=  libOSMesa.so:${PORTSDIR}/graphics/libosmesa

CONFIGURE_ARGS+=--enable-osmesa
PLIST_SUB+=     TOSMESA=""
.else
CONFIGURE_ARGS+=--disable-osmesa
PLIST_SUB+=     TOSMESA="@comment "
.endif

.if ${PORT_OPTIONS:MX11}
CONFIGURE_ARGS+=--enable-x11
PLIST_SUB+=     TX11=""
.else
CONFIGURE_ARGS+=--disable-x11
PLIST_SUB+=     TX11="@comment "
.endif

.if ${PORT_OPTIONS:MEGL}
LIB_DEPENDS+=	libdrm.so:${PORTSDIR}/graphics/libdrm
USE_GL=		glesv2 egl gbm

CONFIGURE_ARGS+=--enable-egl --enable-gbm
CONFIGURE_ARGS+=--enable-gles2 --enable-libdrm
.else
CONFIGURE_ARGS+=--disable-egl --disable-gbm
CONFIGURE_ARGS+=--disable-gles2 --disable-libdrm
.endif

# for now leave disabled
.if ${PORT_OPTIONS:MWAYLAND}
LIB_DEPENDS+=	libwayland-egl.so:${PORTSDIR}/graphics/libEGL		\
		libwayland-client.so:${PORTSDIR}/graphics/wayland

CONFIGURE_ARGS+=--enable-wayland
PLIST_SUB+=     TWAYLAND=""
.else
CONFIGURE_ARGS+=--disable-wayland
PLIST_SUB+=     TWAYLAND="@comment "
.endif

# zrj: install few more programs
dfly-patch:
.if ${PORT_OPTIONS:MZEXTRA}
	${REINPLACE_CMD} -e 's@noinst_PROGRAMS =@bin_PROGRAMS =@g'	\
		${WRKSRC}/src/egl/opengl/Makefile.am			\
		${WRKSRC}/src/redbook/Makefile.am			\
		${WRKSRC}/src/samples/Makefile.am
.endif

.if ${PORT_OPTIONS:MZEXTRA}
PLIST_SUB+=     TEXTRA=""
.else
PLIST_SUB+=     TEXTRA="@comment "
.endif

.if ${PORT_OPTIONS:MZEXTRA} && ${PORT_OPTIONS:MEGL}
PLIST_SUB+=     TEEGL=""
.else
PLIST_SUB+=     TEEGL="@comment "
.endif

.if ${PORT_OPTIONS:MZEXTRA} && ${PORT_OPTIONS:MEGL} && ${PORT_OPTIONS:MX11}
PLIST_SUB+=     TEEX11=""
.else
PLIST_SUB+=     TEEX11="@comment "
.endif


pre-configure:
	cd ${WRKSRC} && ./autogen.sh
# zrj: prevent conflicts with main mesa-demos
	${REINPLACE_CMD} -e "s@PACKAGE='mesa-demos'@PACKAGE='mesa-demos-all'@g"	\
		${WRKSRC}/configure

# zrj: point glsl to DATADIR
post-patch:
	${REINPLACE_CMD} -e "s@\(simplex-noise.glsl\)@${DATADIR}/\1@g"	\
		${WRKSRC}/src/glsl/simplex-noise.c
	${REINPLACE_CMD}						\
		-e "s@\"\([a-zA-Z0-9-]*\.frag\)\"@\"${DATADIR}/\1\"@g"	\
		-e "s@\"\([a-zA-Z0-9-]*\.vert\)\"@\"${DATADIR}/\1\"@g"	\
		${WRKSRC}/src/glsl/blinking-teapot.c			\
		${WRKSRC}/src/glsl/brick.c				\
		${WRKSRC}/src/glsl/bump.c				\
		${WRKSRC}/src/glsl/convolutions.c			\
		${WRKSRC}/src/glsl/mandelbrot.c				\
		${WRKSRC}/src/glsl/multitex.c				\
		${WRKSRC}/src/glsl/skinning.c				\
		${WRKSRC}/src/glsl/texdemo1.c				\
		${WRKSRC}/src/glsl/toyball.c				\
		${WRKSRC}/src/perf/glslstateschange.c
	${REINPLACE_CMD} -e "s@\(leeds.bin\)@${DATADIR}/\1@g"		\
		${WRKSRC}/src/redbook/convolution.c			\
		${WRKSRC}/src/redbook/histogram.c			\
		${WRKSRC}/src/redbook/minmax.c

# install shader sources too
post-install:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/src/glsl/simplex-noise.glsl ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/src/glsl/*.frag ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/src/glsl/*.vert ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/src/perf/*.frag ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/src/perf/*.vert ${STAGEDIR}${DATADIR}
	${INSTALL_DATA} ${WRKSRC}/src/redbook/leeds.bin ${STAGEDIR}${DATADIR}


.include <bsd.port.post.mk>
