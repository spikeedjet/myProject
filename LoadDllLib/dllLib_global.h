#ifndef DLLLIB_GLOBAL_H
#define DLLLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLLIB_LIBRARY)
#define DLLLIB_EXPORT Q_DECL_EXPORT
#define DLLLIB_STATIC
#else
#define DLLLIB_EXPORT Q_DECL_IMPORT
#define DLLLIB_STATIC Q_DECL_IMPORT
#endif

#endif // DLLLIB_GLOBAL_H
