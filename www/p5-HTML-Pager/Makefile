# Created by: will
# $FreeBSD$

PORTNAME=	HTML-Pager
PORTVERSION=	0.03
PORTREVISION=	1
CATEGORIES=	www perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	bofh@FreeBSD.org
COMMENT=	Perl module for handling CGI HTML paging of arbitrary data

LICENSE=	GPLv2

BUILD_DEPENDS=	p5-HTML-Template>=0:${PORTSDIR}/www/p5-HTML-Template
RUN_DEPENDS:=	${BUILD_DEPENDS}

USES=		perl5
USE_PERL5=	configure

.include <bsd.port.mk>
