/*
 * Generated by gdbus-codegen 2.56.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the D-Bus interface description
 * it was derived from.
 */

#ifndef __A_H__
#define __A_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for core.locationd.Session */

#define TYPE_CORE_LOCATIOND_SERVICE_SESSION (core_locationd_service_session_get_type ())
#define CORE_LOCATIOND_SERVICE_SESSION(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION, CoreLocationdServiceSession))
#define IS_CORE_LOCATIOND_SERVICE_SESSION(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION))
#define CORE_LOCATIOND_SERVICE_SESSION_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION, CoreLocationdServiceSessionIface))

struct _CoreLocationdServiceSession;
typedef struct _CoreLocationdServiceSession CoreLocationdServiceSession;
typedef struct _CoreLocationdServiceSessionIface CoreLocationdServiceSessionIface;

struct _CoreLocationdServiceSessionIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_start_heading_updates) (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_start_position_updates) (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_start_velocity_updates) (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_stop_heading_updates) (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_stop_position_updates) (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_stop_velocity_updates) (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

  GVariant * (*get_heading) (CoreLocationdServiceSession *object);

  GVariant * (*get_position) (CoreLocationdServiceSession *object);

  GVariant * (*get_velocity) (CoreLocationdServiceSession *object);

};

GType core_locationd_service_session_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *core_locationd_service_session_interface_info (void);
guint core_locationd_service_session_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void core_locationd_service_session_complete_start_position_updates (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

void core_locationd_service_session_complete_stop_position_updates (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

void core_locationd_service_session_complete_start_velocity_updates (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

void core_locationd_service_session_complete_stop_velocity_updates (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

void core_locationd_service_session_complete_start_heading_updates (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);

void core_locationd_service_session_complete_stop_heading_updates (
    CoreLocationdServiceSession *object,
    GDBusMethodInvocation *invocation);



/* D-Bus method calls: */
void core_locationd_service_session_call_start_position_updates (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean core_locationd_service_session_call_start_position_updates_finish (
    CoreLocationdServiceSession *proxy,
    GAsyncResult *res,
    GError **error);

gboolean core_locationd_service_session_call_start_position_updates_sync (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GError **error);

void core_locationd_service_session_call_stop_position_updates (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean core_locationd_service_session_call_stop_position_updates_finish (
    CoreLocationdServiceSession *proxy,
    GAsyncResult *res,
    GError **error);

gboolean core_locationd_service_session_call_stop_position_updates_sync (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GError **error);

void core_locationd_service_session_call_start_velocity_updates (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean core_locationd_service_session_call_start_velocity_updates_finish (
    CoreLocationdServiceSession *proxy,
    GAsyncResult *res,
    GError **error);

gboolean core_locationd_service_session_call_start_velocity_updates_sync (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GError **error);

void core_locationd_service_session_call_stop_velocity_updates (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean core_locationd_service_session_call_stop_velocity_updates_finish (
    CoreLocationdServiceSession *proxy,
    GAsyncResult *res,
    GError **error);

gboolean core_locationd_service_session_call_stop_velocity_updates_sync (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GError **error);

void core_locationd_service_session_call_start_heading_updates (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean core_locationd_service_session_call_start_heading_updates_finish (
    CoreLocationdServiceSession *proxy,
    GAsyncResult *res,
    GError **error);

gboolean core_locationd_service_session_call_start_heading_updates_sync (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GError **error);

void core_locationd_service_session_call_stop_heading_updates (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean core_locationd_service_session_call_stop_heading_updates_finish (
    CoreLocationdServiceSession *proxy,
    GAsyncResult *res,
    GError **error);

gboolean core_locationd_service_session_call_stop_heading_updates_sync (
    CoreLocationdServiceSession *proxy,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
GVariant *core_locationd_service_session_get_position (CoreLocationdServiceSession *object);
GVariant *core_locationd_service_session_dup_position (CoreLocationdServiceSession *object);
void core_locationd_service_session_set_position (CoreLocationdServiceSession *object, GVariant *value);

GVariant *core_locationd_service_session_get_velocity (CoreLocationdServiceSession *object);
GVariant *core_locationd_service_session_dup_velocity (CoreLocationdServiceSession *object);
void core_locationd_service_session_set_velocity (CoreLocationdServiceSession *object, GVariant *value);

GVariant *core_locationd_service_session_get_heading (CoreLocationdServiceSession *object);
GVariant *core_locationd_service_session_dup_heading (CoreLocationdServiceSession *object);
void core_locationd_service_session_set_heading (CoreLocationdServiceSession *object, GVariant *value);


/* ---- */

#define TYPE_CORE_LOCATIOND_SERVICE_SESSION_PROXY (core_locationd_service_session_proxy_get_type ())
#define CORE_LOCATIOND_SERVICE_SESSION_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION_PROXY, CoreLocationdServiceSessionProxy))
#define CORE_LOCATIOND_SERVICE_SESSION_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_CORE_LOCATIOND_SERVICE_SESSION_PROXY, CoreLocationdServiceSessionProxyClass))
#define CORE_LOCATIOND_SERVICE_SESSION_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION_PROXY, CoreLocationdServiceSessionProxyClass))
#define IS_CORE_LOCATIOND_SERVICE_SESSION_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION_PROXY))
#define IS_CORE_LOCATIOND_SERVICE_SESSION_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_CORE_LOCATIOND_SERVICE_SESSION_PROXY))

typedef struct _CoreLocationdServiceSessionProxy CoreLocationdServiceSessionProxy;
typedef struct _CoreLocationdServiceSessionProxyClass CoreLocationdServiceSessionProxyClass;
typedef struct _CoreLocationdServiceSessionProxyPrivate CoreLocationdServiceSessionProxyPrivate;

struct _CoreLocationdServiceSessionProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  CoreLocationdServiceSessionProxyPrivate *priv;
};

struct _CoreLocationdServiceSessionProxyClass
{
  GDBusProxyClass parent_class;
};

GType core_locationd_service_session_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CoreLocationdServiceSessionProxy, g_object_unref)
#endif

void core_locationd_service_session_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
CoreLocationdServiceSession *core_locationd_service_session_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
CoreLocationdServiceSession *core_locationd_service_session_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void core_locationd_service_session_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
CoreLocationdServiceSession *core_locationd_service_session_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
CoreLocationdServiceSession *core_locationd_service_session_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_CORE_LOCATIOND_SERVICE_SESSION_SKELETON (core_locationd_service_session_skeleton_get_type ())
#define CORE_LOCATIOND_SERVICE_SESSION_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION_SKELETON, CoreLocationdServiceSessionSkeleton))
#define CORE_LOCATIOND_SERVICE_SESSION_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_CORE_LOCATIOND_SERVICE_SESSION_SKELETON, CoreLocationdServiceSessionSkeletonClass))
#define CORE_LOCATIOND_SERVICE_SESSION_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION_SKELETON, CoreLocationdServiceSessionSkeletonClass))
#define IS_CORE_LOCATIOND_SERVICE_SESSION_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_CORE_LOCATIOND_SERVICE_SESSION_SKELETON))
#define IS_CORE_LOCATIOND_SERVICE_SESSION_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_CORE_LOCATIOND_SERVICE_SESSION_SKELETON))

typedef struct _CoreLocationdServiceSessionSkeleton CoreLocationdServiceSessionSkeleton;
typedef struct _CoreLocationdServiceSessionSkeletonClass CoreLocationdServiceSessionSkeletonClass;
typedef struct _CoreLocationdServiceSessionSkeletonPrivate CoreLocationdServiceSessionSkeletonPrivate;

struct _CoreLocationdServiceSessionSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  CoreLocationdServiceSessionSkeletonPrivate *priv;
};

struct _CoreLocationdServiceSessionSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType core_locationd_service_session_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CoreLocationdServiceSessionSkeleton, g_object_unref)
#endif

CoreLocationdServiceSession *core_locationd_service_session_skeleton_new (void);


G_END_DECLS

#endif /* __A_H__ */
