# Created by: zRJ@ef

PORTNAME=	mesa-pack
PORTVERSION=	${MESAVERSION}
PORTREVISION=	0
CATEGORIES=	graphics

COMMENT=	Mesa single build package for testing and subpackets

MESABASEVERSION=	10.6.9
# if there is a subversion, don't include the '-' between 7.11-rc2.
MESASUBVERSION=

MESAVERSION=	${MESABASEVERSION}${MESASUBVERSION:C/^(.)/.\1/}
MESADISTVERSION=${MESABASEVERSION}${MESASUBVERSION:C/^(.)/-\1/}

MASTER_SITES=	ftp://ftp.freedesktop.org/pub/mesa/${MESABASEVERSION}/

DISTFILES=	mesa-${MESADISTVERSION}${EXTRACT_SUFX}

MAINTAINER=	zRJ@ef

MESA_FLAVOUR?= stock
MESA_LLVM_VER=36

BUILD_DEPENDS+=	makedepend:${PORTSDIR}/devel/makedepend

USES+=		compiler:c++11-lib gettext-tools gmake libtool \
		pathfix pkgconfig python:2,build shebangfix tar:xz
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes
CPPFLAGS+=	-isystem${LOCALBASE}/include
LDFLAGS+=	-Wl,-Y${LOCALBASE}/lib


#USE_XORG=	glproto x11 xext xxf86vm xdamage xfixes dri2proto:both \
#		presentproto xshmfence

OPTIONS_DEFINE=		CLOVER DRI DRID EGL GALLIUM GBM \
			GLAPI GLESV2 GLX OPENGL OSMESAS OSMESAG \
			TESTS TEXTURE XVMC VAAPI VDPAU
OPTIONS_DEFAULT=	CLOVER DRI DRID EGL GALLIUM GBM \
			GLAPI GLESV2 GLX OPENGL OSMESAG \
			TESTS TEXTURE XVMC VAAPI VDPAU \
			EX11 EDRM R300 R600 RADEONSI SVGA

OPTIONS_GROUP=		EPLAT GDRIVERS
OPTIONS_GROUP_EPLAT=	EX11 EDRM EWAYLAND
OPTIONS_GROUP_GDRIVERS=	I915 R300 R600 RADEONSI SVGA

OPTIONS_SUB=		yes

CLOVER_DESC=	Mesa "Clover" OpenCL library                         [clang]
DRI_DESC=	OpenGL acceleration drivers for the DRI (needs OPENGL)
DRID_DESC=	DRI classic drivers for Xorg (needs DRI)
EGL_DESC=	Shared EGL library libEGL.so (requires DRI,GLAPI)
GALLIUM_DESC=	Modern Gallium3D drivers (swrast included)            [LLVM]
GBM_DESC=	General Buffer Management API for EGL (requires DRI,GLAPI)
GLAPI_DESC=	Shared GL API library (needs OPENGL)
GLESV2_DESC=	Shared OpenGL ES 2.x API library (needs OPENGL,GLAPI)
GLX_DESC=	Shared GLX library libGL.so (needs OPENGL,DRI,GLAPI)   [X11]
OPENGL_DESC=	OpenGL headers
OSMESAS_DESC=	Off-Screen Mesa variant of OpenGL API (needs OPENGL)
OSMESAG_DESC=	Off-Screen Mesa Gallium variant (needs OPENGL,GALLIUM)
TESTS_DESC=	Enable tests and run them after install
TEXTURE_DESC=	Enable texture-float support (patent encumbered)
XVMC_DESC=	XvMC deprecated video driver (requires R600!)          [X11]
VAAPI_DESC=	VAAPI (GPU video acceleration) support (needs Gallium) [X11]
VDPAU_DESC=	VDPAU (GPU video acceleration) support (needs Gallium) [X11]

EPLAT_DESC=	Native platforms support in libEGL, Order matters!
EX11_DESC=	x11 platform (for ABI keep x11 first on list or else)  [X11]
EDRM_DESC=	drm platform (requires GBM)
EWAYLAND_DESC=	Wayland platform

GDRIVERS_DESC=	Gallium drivers list (only active if GALLIUM)
I915_DESC=	i915/i945 (has few issues) [experimental only]
R300_DESC=	ATI R300-R500 cards
R600_DESC=	ATI/AMD R600-Northern Island(NI)
RADEONSI_DESC=	AMD Southern Island(SI)
SVGA_DESC=	VMware virtual GPU driver (need kernel driver?)

.include <bsd.port.pre.mk>

.if ${OPSYS} == FreeBSD && ${OSVERSION} < 1000033
BUILD_DEPENDS+=	${LOCALBASE}/bin/flex:${PORTSDIR}/textproc/flex
CONFIGURE_ENV+=	ac_cv_prog_LEX=${LOCALBASE}/bin/flex
.endif

# and don't forget to include it as run_depends (-ldl)
BUILD_DEPENDS+=	${LOCALBASE}/lib/libdevq.so:${PORTSDIR}/devel/libdevq

# just assume it is needed, xml
BUILD_DEPENDS+=	${LOCALBASE}/lib/libexpat.so:${PORTSDIR}/textproc/expat2

# just in case, even if defaults
CONFIGURE_ARGS+=	--disable-sysfs --disable-selinux

# OpenMAX library, what to do with it?
CONFIGURE_ARGS+=	--disable-omx

# vmware 3D api?
CONFIGURE_ARGS+=	--disable-xa

# We not there yet, PRIME
CONFIGURE_ARGS+=	--disable-dri3

# Disable glesv1_cm, not needed
CONFIGURE_ARGS+=	--disable-gles1

.if ${PORT_OPTIONS:MTESTS} && ${PORT_OPTIONS:MGALLIUM}
CONFIGURE_ARGS+=	--enable-gallium-tests
.endif

.if ${PORT_OPTIONS:MCLOVER}
# looks like still uses internal (standalone mode) CL headers, but better safe than sorry
BUILD_DEPENDS+=	opencl>=0:${PORTSDIR}/devel/opencl
# this one is not supposed to be needed by OpenCL implementations themselves,
# only for actual programs that uses proxy (libOpenCL.so), maybe as RUN_DEPENDS makes sense
#BUILD_DEPENDS+= ${LOCALBASE}/lib/libOpenCL.so:${PORTSDIR}/devel/ocl-icd

BUILD_DEPENDS+=	clang${MESA_LLVM_VER}>=0:${PORTSDIR}/lang/clang${MESA_LLVM_VER}

.if ${OPSYS} == DragonFly || \
	(${OPSYS} == FreeBSD && ${OSVERSION} >= 1000000 && \
	 (${ARCH} == i386 || ${ARCH} == x86_64))
BUILD_DEPENDS+=	libclc>=0.0.r222830:${PORTSDIR}/devel/libclc
.endif
CONFIGURE_ARGS+= --enable-opencl --enable-opencl-icd
PLIST_SUB+=     CLOVER=""
.else
CONFIGURE_ARGS+= --disable-opencl --disable-opencl-icd
PLIST_SUB+=     CLOVER="@comment "
.endif

.if ${PORT_OPTIONS:MDRI}
BUILD_DEPENDS+=	${LOCALBASE}/libdata/pkgconfig/libdrm.pc:${PORTSDIR}/graphics/libdrm
CONFIGURE_ARGS+=	--enable-dri
PLIST_SUB+=     DRI=""
.else
CONFIGURE_ARGS+=	--disable-dri
PLIST_SUB+=     DRI="@comment "
.endif

.if ${PORT_OPTIONS:MEGL}
CONFIGURE_ARGS+=	--enable-egl
PLIST_SUB+=     EGL=""
.else
CONFIGURE_ARGS+=	--disable-egl
PLIST_SUB+=     EGL="@comment "
.endif

.if ${PORT_OPTIONS:MGALLIUM}
# libelf only mandatory for radeonsi gallium drivers (RADEONSI) and CLOVER
.if ${OPSYS} == DragonFly
BUILD_DEPENDS+= ${LOCALBASE}/lib/libelf.so:${PORTSDIR}/devel/libelf
CFLAGS+= -I${LOCALBASE}/include/libelf
.endif
BUILD_DEPENDS+= llvm${MESA_LLVM_VER}>=0:${PORTSDIR}/devel/llvm${MESA_LLVM_VER}
CONFIGURE_ENV+= LLVM_CONFIG=${LOCALBASE}/bin/llvm-config${MESA_LLVM_VER}
CONFIGURE_ARGS+= --enable-gallium-llvm
PLIST_SUB+=     GALLIUM=""
.else
CONFIGURE_ARGS+= --disable-gallium-llvm
PLIST_SUB+=     GALLIUM="@comment "
.endif

# zrj whats the point of separating gbm and libEGL???
.if ${PORT_OPTIONS:MGBM}
CONFIGURE_ARGS+=	--enable-gbm
PLIST_SUB+=     GBM=""
.else
CONFIGURE_ARGS+=	--disable-gbm
PLIST_SUB+=     GBM="@comment "
.endif

.if ${PORT_OPTIONS:MGLAPI}
CONFIGURE_ARGS+=	--enable-shared-glapi
PLIST_SUB+=     GLAPI=""
.else
CONFIGURE_ARGS+=	--disable-shared-glapi
PLIST_SUB+=     GLAPI="@comment "
.endif

.if ${PORT_OPTIONS:MGLESV2}
CONFIGURE_ARGS+=	--enable-gles2
PLIST_SUB+=     GLESV2=""
.else
CONFIGURE_ARGS+=	--disable-gles2
PLIST_SUB+=     GLESV2="@comment "
.endif

.if ${PORT_OPTIONS:MGLX}
#Requires.private:  libdrm >= 2.4.38 x11 xext xdamage xfixes x11-xcb xcb xcb-glx >= 1.8.1 xcb-dri2 >= 1.8 xxf86vm
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/glproto.pc:${PORTSDIR}/x11/glproto
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri2proto.pc:${PORTSDIR}/x11/dri2proto
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri3proto.pc:${PORTSDIR}/x11/dri3proto
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/x11.pc:${PORTSDIR}/x11/libX11
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xext.pc:${PORTSDIR}/x11/libXext
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xdamage.pc:${PORTSDIR}/x11/libXdamage
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xfixes.pc:${PORTSDIR}/x11/libXfixes
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xcb.pc:${PORTSDIR}/x11/libxcb
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xxf86vm.pc:${PORTSDIR}/x11/libXxf86vm
# not sure if needed here (not needed, no impact)
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/presentproto.pc:${PORTSDIR}/x11/presentproto
# this one only needed for dri3 (not needed, no impact)
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xshmfence.pc:${PORTSDIR}/x11/libxshmfence

CONFIGURE_ARGS+=	--enable-glx
PLIST_SUB+=     GLX=""
.else
CONFIGURE_ARGS+=	--disable-glx
PLIST_SUB+=     GLX="@comment "
.endif

.if ${PORT_OPTIONS:MOPENGL}
CONFIGURE_ARGS+=	--enable-opengl
PLIST_SUB+=     OPENGL=""
.else
CONFIGURE_ARGS+=	--disable-opengl
PLIST_SUB+=     OPENGL="@comment "
.endif

.if ${PORT_OPTIONS:MOSMESAS}
CONFIGURE_ARGS+=	--enable-osmesa
.else
CONFIGURE_ARGS+=	--disable-osmesa
.endif

.if ${PORT_OPTIONS:MOSMESAG}
CONFIGURE_ARGS+=	--enable-gallium-osmesa
.else
CONFIGURE_ARGS+=	--disable-gallium-osmesa
.endif

.if ${PORT_OPTIONS:MOSMESAS} || ${PORT_OPTIONS:MOSMESAG}
PLIST_SUB+=     TOSMESA=""
.else
PLIST_SUB+=     TOSMESA="@comment "
.endif

.if ${PORT_OPTIONS:MTEXTURE}
CONFIGURE_ARGS+=	--enable-texture-float
.else
CONFIGURE_ARGS+=	--disable-texture-float
.endif


### EGL platforms
# empty
_EGL_PLATFORMS=

.if ${PORT_OPTIONS:MEX11}
# x11-xcb xcb xcb-dri2 >= 1.8 xcb-xfixes + same ones as GLX if enabled
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xcb.pc:${PORTSDIR}/x11/libxcb
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/x11-xcb.pc:${PORTSDIR}/x11/libX11

_EGL_PLATFORMS+= x11
.endif

.if ${PORT_OPTIONS:MEDRM}
_EGL_PLATFORMS+= drm
.endif

.if ${PORT_OPTIONS:MEWAYLAND}
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/wayland-client.pc:${PORTSDIR}/graphics/wayland
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/wayland-server.pc:${PORTSDIR}/graphics/wayland
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/wayland-scanner.pc:${PORTSDIR}/graphics/wayland
BUILD_DEPENDS+= ${LOCALBASE}/lib/libwayland-client.so:${PORTSDIR}/graphics/wayland
BUILD_DEPENDS+= ${LOCALBASE}/lib/libwayland-server.so:${PORTSDIR}/graphics/wayland
_EGL_PLATFORMS+= wayland
PLIST_SUB+=     EWAYLAND=""
.else
PLIST_SUB+=     EWAYLAND="@comment "
.endif

__EGL_PLATFORMS!= ${ECHO_CMD} ${_EGL_PLATFORMS} | ${SED} -e 's/ /,/g'
CONFIGURE_ARGS+=--with-egl-platforms="${__EGL_PLATFORMS}"

### end EGL platforms

# Driver fun

### VA-API driver (currently disabled by default) requires external libGL.so
.if ${PORT_OPTIONS:MVAAPI}
# has recursive dependency on libGL, needs only libva headers to build driver
##BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/libva.pc:${PORTSDIR}/multimedia/libva
BUILD_DEPENDS+=	${LOCALBASE}/include/linux/videodev2.h:${PORTSDIR}/multimedia/v4l_compat

# x11-xcb xcb xcb-dri2 >= 1.8 xcb-xfixes + same ones as GLX if enabled
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xcb.pc:${PORTSDIR}/x11/libxcb
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/x11-xcb.pc:${PORTSDIR}/x11/libX11
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri2proto.pc:${PORTSDIR}/x11/dri2proto

# some monkey business to break circular deps early
CONFIGURE_ENV+= VA_CFLAGS="-I." VA_LIBS="-lva"
EXTRA_PATCHES+=	${FILESDIR}/extra-patch-libva_headers_bootstrap

CONFIGURE_ARGS+=	--enable-va
PLIST_SUB+=     VAAPI=""
.else
CONFIGURE_ARGS+=	--disable-va
PLIST_SUB+=     VAAPI="@comment "
.endif

### deprecated XvMCr600 driver
.if ${PORT_OPTIONS:MXVMC}
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri2proto.pc:${PORTSDIR}/x11/dri2proto
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri3proto.pc:${PORTSDIR}/x11/dri3proto

BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/xvmc.pc:${PORTSDIR}/x11/libXvMC

CONFIGURE_ARGS+=	--enable-xvmc
PLIST_SUB+=     R600_XVMC=""
.else
CONFIGURE_ARGS+=	--disable-xvmc
PLIST_SUB+=     R600_XVMC="@comment "
.endif

### VDPAU drivers
ALL_VDPAU_DRIVERS=R300 R600 RADEONSI

.if ${PORT_OPTIONS:MVDPAU}
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri2proto.pc:${PORTSDIR}/x11/dri2proto
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/dri3proto.pc:${PORTSDIR}/x11/dri3proto

CONFIGURE_ARGS+=--enable-vdpau
BUILD_DEPENDS+= ${LOCALBASE}/libdata/pkgconfig/vdpau.pc:${PORTSDIR}/multimedia/libvdpau
#BUILD_DEPENDS+= ${LOCALBASE}/liblibvdpau.so:${PORTSDIR}/multimedia/libvdpau
.else
CONFIGURE_ARGS+=--disable-vdpau
.endif

.for _gd in ${ALL_VDPAU_DRIVERS}
. if ${PORT_OPTIONS:M${_gd}} && ${PORT_OPTIONS:MVDPAU}
PLIST_SUB+=	${_gd}_VDPAU=""
. else
PLIST_SUB+=	${_gd}_VDPAU="@comment "
. endif
.endfor
### end VDPAU drivers


# swrast drivers are handled differently! courtesy of llvm..

### now lets handle clasic driver options, for now excluding nouveau
# dri drivers require both OpenGL and DRI
ALL_DRI_DRIVERS=I915 I965 R200 RADEON

.if ${PORT_OPTIONS:MDRID}

.if ${ARCH} == x86_64 || ${ARCH} == i386 || ${ARCH} == ia64
DRI_DRIVERS=	${ALL_DRI_DRIVERS}
.endif

.if ${ARCH} == powerpc || ${ARCH} == powerpc64
DRI_DRIVERS=	RADEON
.endif

_DRI_DRIVERS+= ${DRI_DRIVERS}
_DRI_DRIVERS+= SWRAST
__DRI_DRIVERS!= ${ECHO_CMD} ${_DRI_DRIVERS:tl} | ${SED} -e 's/ /,/g'
CONFIGURE_ARGS+=--with-dri-drivers="${__DRI_DRIVERS}"
.else
CONFIGURE_ARGS+=--with-dri-drivers=""
.endif

# empty for unsupported arches
DRI_DRIVERS+=
.for _d in ${ALL_DRI_DRIVERS}
. if ${DRI_DRIVERS:M${_d}}
PLIST_SUB+=	${_d}_DRIVER=""
. else
PLIST_SUB+=	${_d}_DRIVER="@comment "
. endif
.endfor
### end now lets handle clasic drivers options


### now lets handle modern drivers, for now excluding nouveau

# sadly llvm is only enabled if --with-gallium-drivers is not empty...
# also for DRI+DRID+GALLIUM swrast_dri.so becomes gallium driver...
# also also for DRI+GALLIUM swrast_dri.so installed too like in DRI+DRID
#      even if --with-dri-drivers=""
.if ${PORT_OPTIONS:MDRID} || (${PORT_OPTIONS:MGALLIUM} && ${PORT_OPTIONS:MDRI})
PLIST_SUB+=     SWRAST_DRIVER=""
.else
PLIST_SUB+=     SWRAST_DRIVER="@comment "
.endif
.if ${PORT_OPTIONS:MGALLIUM} && ${PORT_OPTIONS:MDRI}
PLIST_SUB+=     SWRAST_GDRIVER=""
.else
PLIST_SUB+=     SWRAST_GDRIVER="@comment "
.endif

# empty
_GALLIUM_DRIVERS=
GALLIUM_DRIVERS=

# dri-state drivers to consider
ALL_GALLIUM_DRIVERS=I915 R300 R600 RADEONSI SVGA

.if ${PORT_OPTIONS:MGALLIUM}
# swrast needed by most components like osmesa-gallium & clover
_GALLIUM_DRIVERS=SWRAST

# only consider gallium drivers if dri is enabled too
.  if ${PORT_OPTIONS:MDRI}
.if ${ARCH} == x86_64 || ${ARCH} == i386 || ${ARCH} == ia64
GALLIUM_DRIVERS=I915 R300 R600 RADEONSI SVGA
.endif

# zrj: gallium xradeon ???
#.if ${ARCH} == powerpc || ${ARCH} == powerpc64
#GALLIUM_DRIVERS=	RADEON
#.endif
.  endif
.endif

.for _gd in ${ALL_GALLIUM_DRIVERS}
. if ${PORT_OPTIONS:M${_gd}} && ${GALLIUM_DRIVERS:M${_gd}}
_GALLIUM_DRIVERS+=${_gd}
PLIST_SUB+=	${_gd}_GDRIVER=""
. else
PLIST_SUB+=	${_gd}_GDRIVER="@comment "
. endif
.endfor

__GALLIUM_DRIVERS!= ${ECHO_CMD} ${_GALLIUM_DRIVERS:tl} | ${SED} -e 's/ /,/g'
CONFIGURE_ARGS+= --with-gallium-drivers="${__GALLIUM_DRIVERS}"

### end now lets handle modern drivers


### now lets deal with pipe drivers (OpenCL)

# NOTE: produces different pipe_swrast.so if DRI is OFF

# clover dri-state drivers to consider, swrast is already in CLOVER
ALL_CLOVER_DRIVERS=I915 R300 R600 RADEONSI SVGA

.for _gd in ${ALL_CLOVER_DRIVERS}
. if ${PORT_OPTIONS:M${_gd}} && ${PORT_OPTIONS:MCLOVER}
PLIST_SUB+=	${_gd}_CLOVER=""
. else
PLIST_SUB+=	${_gd}_CLOVER="@comment "
. endif
.endfor

### end now lets deal with pipe drivers (OpenCL)


.if 1
# IGNORE blocks
.if ${PORT_OPTIONS:MCLOVER} && (${PORT_OPTIONS:MOPENGL} == "" || \
	${PORT_OPTIONS:MGALLIUM} == "")
IGNORE= CLOVER needs OPENGL,GALLIUM options (missing targets)
.endif

.if ${PORT_OPTIONS:MDRI} && ${PORT_OPTIONS:MOPENGL} == ""
IGNORE= DRI option needs OPENGL headers (missing targets)
.endif

.if ${PORT_OPTIONS:MDRID} && ${PORT_OPTIONS:MDRI} == ""
IGNORE= DRID option needs DRI (configure fail)
.endif

.if ${PORT_OPTIONS:MGBM} && (${PORT_OPTIONS:MOPENGL} == "" || \
	${PORT_OPTIONS:MDRI} == "" || ${PORT_OPTIONS:MGLAPI} == "")
IGNORE= GBM option needs OPENGL,DRI,GLAPI  (configure fail)
.endif

.if ${PORT_OPTIONS:MGALLIUM} && ${PORT_OPTIONS:MOPENGL} == ""
IGNORE= GALLIUM option needs OPENGL (configure fail)
.endif

.if ${PORT_OPTIONS:MGLAPI} && ${PORT_OPTIONS:MOPENGL} == ""
IGNORE= GLAPI option needs OPENGL or XVMC (configure fail)
.endif

.if ${PORT_OPTIONS:MGLESV2} && ${PORT_OPTIONS:MGLAPI} == ""
IGNORE= GLESV2 option needs OPENGL,GLAPI (configure fail)
.endif

.if ${PORT_OPTIONS:MGLX} && ${PORT_OPTIONS:MDRI} == ""
IGNORE= GLX options needs DRI (alternative --enable-xlib-glx but...)
.endif

.if ${PORT_OPTIONS:MGLX} && ${PORT_OPTIONS:MDRI} && ${PORT_OPTIONS:MGLAPI} == ""
IGNORE= GLX+DRI options need GLAPI (unit test fail in glapi symbols)
.endif

.if ${PORT_OPTIONS:MEGL} && (${PORT_OPTIONS:MOPENGL} == "" || \
	${PORT_OPTIONS:MDRI} == "" || ${PORT_OPTIONS:MGLAPI} == "")
IGNORE= EGL option needs OPENGL,DRI,GLAPI  (configure fail)
.endif

.if ${PORT_OPTIONS:MOSMESAS} && ${PORT_OPTIONS:MOSMESAG}
IGNORE= Can not use both OSMESAS OSMESAG (configure fail)
.endif

.if ${PORT_OPTIONS:MOSMESAS} && ${PORT_OPTIONS:MOPENGL} == ""
IGNORE= OSMESAS option needs OPENGL headers (empty port)
.endif

.if ${PORT_OPTIONS:MOSMESAG} && (${PORT_OPTIONS:MOPENGL} == "" || \
	${PORT_OPTIONS:MGALLIUM} == "")
IGNORE= OSMESAG(Gallium) needs GALLIUM (requires gallium-swrast driver)
.endif


.if ${PORT_OPTIONS:MXVMC} && (${PORT_OPTIONS:MGALLIUM} == "" || \
	${PORT_OPTIONS:MDRI} == "" || ${PORT_OPTIONS:MR600} == "")
IGNORE= XVMC needs GALLIUM,DRI,R600 options (empty port)
.endif

.if ${PORT_OPTIONS:MVAAPI} && ${PORT_OPTIONS:MGALLIUM} == ""
IGNORE= VAAPI needs GALLIUM options (empty port)
.endif

.if ${PORT_OPTIONS:MVDPAU} && ( \
	(${PORT_OPTIONS:MGALLIUM} == "" || ${PORT_OPTIONS:MDRI} == "") || \
	(${PORT_OPTIONS:MR300} == "" && ${PORT_OPTIONS:MR600} == "" && \
	${PORT_OPTIONS:MRADEONSI} == ""))
IGNORE= VDPAU needs GALLIUM,DRI and any R300,R600,RADEONSI option (empty port)
.endif


.if (${PORT_OPTIONS:MEX11} || ${PORT_OPTIONS:MEDRM} || \
	${PORT_OPTIONS:MEWAYLAND}) && ${PORT_OPTIONS:MEGL} == ""
IGNORE= EGL native platforms need EGL option (configure fail)
.endif

.if ${PORT_OPTIONS:MEDRM} && ${PORT_OPTIONS:MGBM} == ""
IGNORE= DRM native platform on EGL needs GBM (configure fail)
.endif

.if (${PORT_OPTIONS:MR300} || ${PORT_OPTIONS:MR600} || \
	${PORT_OPTIONS:MRADEONSI} || ${PORT_OPTIONS:MSVGA}) && \
	(${PORT_OPTIONS:MGALLIUM} == "" || ${PORT_OPTIONS:MDRI} == "")
IGNORE= Gallium drivers need GALLIUM,DRI options (just go with it)
.endif

.if ${PORT_OPTIONS:MRADEONSI} && ${PORT_OPTIONS:MDRI} && \
	${PORT_OPTIONS:MGALLIUM} && ${PORT_OPTIONS:MEDRM} == ""
IGNORE= RADEONSI Gallium driver requires EDRM (--with-egl-platforms=drm)
.endif

.if ${PORT_OPTIONS:MI915} && ${PORT_OPTIONS:MGALLIUM} == ""
IGNORE= I915 Gallium driver needs GALLIUM,DRI options (empty port)
.endif

.endif # IGNORE blocks


# python fun
python_OLD_CMD=	"/usr/bin/env[[:space:]]python"
python_CMD=	${LOCALBASE}/bin/python2
SHEBANG_FILES=	src/gallium/*/*/*.py src/gallium/tools/trace/*.py \
		src/gallium/drivers/svga/svgadump/svga_dump.py \
		src/glsl/tests/compare_ir src/mapi/glapi/gen/*.py
SHEBANG_FILES+=	src/mapi/mapi_abi.py
### bash fun
###SHEBANG_FILES+= src/gbm/gbm-symbols-check

WRKSRC=			${WRKDIR}/mesa-${MESADISTVERSION}
INSTALL_TARGET=		install-strip

#IGNORE= ${LIB_DEPENDS} ${RUN_DEPENDS} zzz

post-patch:
#	Sed on 9.x and dragonfly don't support \< or \>
	@${REINPLACE_CMD} \
		-e 's|\\>//|[[:>:]]//|' \
		-e 's|python2 python|python2disabled pythondisabled|g' \
		${WRKSRC}/configure
	@${REINPLACE_CMD} -e 's|bin/bash|bin/sh|g'			\
		${WRKSRC}/src/gbm/gbm-symbols-check			\
		${WRKSRC}/src/mapi/es1api/ABI-check			\
		${WRKSRC}/src/mapi/es2api/ABI-check			\
		${WRKSRC}/src/egl/wayland/wayland-egl/wayland-egl-symbols-check
	@${REINPLACE_CMD} -e 's|/etc/|${PREFIX}/etc/|g' \
		${WRKSRC}/src/mesa/drivers/dri/common/xmlconfig.c
	@${REINPLACE_CMD} -e 's|#!/use/bin/python|#!${PYTHON_CMD}|g' \
		${WRKSRC}/src/mesa/drivers/dri/common/xmlpool/gen_xmlpool.py
	@${REINPLACE_CMD} -e 's|!/use/bin/python2|!${PYTHON_CMD}|g' \
		${WRKSRC}/src/mesa/main/get_hash_generator.py \
		${WRKSRC}/src/mapi/glapi/gen/gl_enums.py \
		${WRKSRC}/src/mapi/glapi/gen/gl_table.py

# zrj: 1) move OpenCL 2) prep .mesa-pack 3) prune empty dirs in .mesa-pack 4) TESTS
post-install:
.if ${PORT_OPTIONS:MCLOVER}
	-@${MV} ${STAGEDIR}/etc/OpenCL ${STAGEDIR}${PREFIX}/etc/
.endif
	( ${MV} ${STAGEDIR}${PREFIX} ${STAGEDIR}/.mesa-pack && \
		${MKDIR} -p ${STAGEDIR}${PREFIX} && \
		${MV} ${STAGEDIR}/.mesa-pack ${STAGEDIR}${PREFIX}/ )
	@${FIND} "${STAGEDIR}${PREFIX}/.mesa-pack" -type d -empty -delete
	${ECHO_MSG} "PORTREVISION:${PORTREVISION}" > "${STAGEDIR}${PREFIX}/.mesa-pack/MESAOPTIONS"
	${ECHO_MSG} "MESA_VERSION:${MESAVERSION}" >> "${STAGEDIR}${PREFIX}/.mesa-pack/MESAOPTIONS"
	${ECHO_MSG} "MESA_FLAVOUR:${MESA_FLAVOUR}" >> "${STAGEDIR}${PREFIX}/.mesa-pack/MESAOPTIONS"
	${ECHO_MSG} "MESA_LLVM_VER:${MESA_LLVM_VER}" >> "${STAGEDIR}${PREFIX}/.mesa-pack/MESAOPTIONS"
.for opt in ${PORT_OPTIONS}
	${ECHO_MSG} " ${opt}" >> "${STAGEDIR}${PREFIX}/.mesa-pack/MESAOPTIONS"
.endfor
.if ${PORT_OPTIONS:MTESTS}
	(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} gmake ${_MAKE_JOBS} ${MAKE_ARGS} check)
.endif

# zrj: enforce check-plist
pre-package: check-plist

check-already-installed: check-plist


.include <bsd.port.post.mk>
