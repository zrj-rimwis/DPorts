# Created by: Alex Trull <freebsd.alex@trull.org>
# $FreeBSD$

PORTNAME=	scummvm
DISTVERSION=	1.7.0
PORTREVISION=	4
CATEGORIES=	games emulators
MASTER_SITES=	SF

MAINTAINER=	lme@FreeBSD.org
COMMENT=	Interpreter for several adventure games

USES=		gmake jpeg tar:bzip2
HAS_CONFIGURE=	yes
USE_SDL=	sdl

CONFIGURE_ARGS=	--with-sdl-prefix=${LOCALBASE} \
		--with-jpeg-prefix=${LOCALBASE} \
		--disable-alsa \
		--with-zlib-prefix=/usr \
		--disable-debug \
		--disable-nasm \
		--disable-tremor

.if defined(BATCH) || defined(PACKAGE_BUILDING)
CONFIGURE_ARGS+=	--enable-verbose-build
.endif

LDFLAGS+=	-lpthread

OPTIONS_DEFINE=	VORBIS MP3 PNG FLAC FLUIDSYNTH MT32EMU DOCS
FLUIDSYNTH_DESC=	FluidSynth MIDI synthesizer
MT32EMU_DESC=	MT-32 emulator
OPTIONS_DEFAULT=	VORBIS MP3 PNG MT32EMU

VORBIS_LIB_DEPENDS=	libogg.so:${PORTSDIR}/audio/libogg \
			libvorbis.so:${PORTSDIR}/audio/libvorbis
VORBIS_CONFIGURE_ON=	--with-ogg-prefix=${LOCALBASE} \
			--with-vorbis-prefix=${LOCALBASE}
VORBIS_CONFIGURE_OFF=	--disable-vorbis

MP3_LIB_DEPENDS=	libmad.so:${PORTSDIR}/audio/libmad
MP3_CONFIGURE_ON=	--with-mad-prefix=${LOCALBASE}
MP3_CONFIGURE_OFF=	--disable-mad

PNG_LIB_DEPENDS=	libpng.so:${PORTSDIR}/graphics/png
PNG_CONFIGURE_ON=	--with-png-prefix=${LOCALBASE}
PNG_CONFIGURE_OFF=	--disable-png

FLAC_LIB_DEPENDS=	libFLAC.so:${PORTSDIR}/audio/flac
FLAC_CONFIGURE_ON=	--with-flac-prefix=${LOCALBASE}
FLAC_CONFIGURE_OFF=	--disable-flac

FLUIDSYNTH_LIB_DEPENDS=		libfluidsynth.so:${PORTSDIR}/audio/fluidsynth
FLUIDSYNTH_CONFIGURE_ON=	--with-fluidsynth-prefix=${LOCALBASE}
FLUIDSYNTH_CONFIGURE_OFF=	--disable-fluidsynth

MT32EMU_CONFIGURE_OFF=	--disable-mt32emu

.include <bsd.port.pre.mk>

.if ${ARCH} == "armv6"
CONFIGURE_ENV+=	ASFLAGS=-meabi=5
.endif

post-patch:
	@${REINPLACE_CMD} -e '/^mandir=/s/datarootdir/prefix/' \
		${WRKSRC}/configure

post-install:
	@${MKDIR} ${STAGEDIR}${DESKTOPDIR}
	${INSTALL_DATA} ${WRKSRC}/dists/${PORTNAME}.desktop \
		${STAGEDIR}${DESKTOPDIR}
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

.include <bsd.port.post.mk>
