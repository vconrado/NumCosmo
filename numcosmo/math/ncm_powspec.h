/***************************************************************************
 *            ncm_powspec.h
 *
 *  Tue February 16 17:01:03 2016
 *  Copyright  2016  Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * ncm_powspec.h
 * Copyright (C) 2016 Sandro Dias Pinto Vitenti <sandro@isoftware.com.br>
 *
 * numcosmo is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * numcosmo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NCM_POWSPEC_H_
#define _NCM_POWSPEC_H_

#include <glib.h>
#include <glib-object.h>
#include <numcosmo/build_cfg.h>
#include <numcosmo/math/ncm_model_ctrl.h>

G_BEGIN_DECLS

#define NCM_TYPE_POWSPEC             (ncm_powspec_get_type ())
#define NCM_POWSPEC(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), NCM_TYPE_POWSPEC, NcmPowspec))
#define NCM_POWSPEC_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), NCM_TYPE_POWSPEC, NcmPowspecClass))
#define NCM_IS_POWSPEC(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NCM_TYPE_POWSPEC))
#define NCM_IS_POWSPEC_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), NCM_TYPE_POWSPEC))
#define NCM_POWSPEC_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), NCM_TYPE_POWSPEC, NcmPowspecClass))

typedef struct _NcmPowspecClass NcmPowspecClass;
typedef struct _NcmPowspec NcmPowspec;

struct _NcmPowspecClass
{
  /*< private > */
  GObjectClass parent_class;
  void (*prepare) (NcmPowspec *powspec, NcmModel *model);
  gdouble (*eval) (NcmPowspec *powspec, NcmModel *model, const gdouble z, const gdouble k);
};

struct _NcmPowspec
{
  /*< private > */
  GObject parent_instance;
  gdouble zi;
  gdouble zf;
  gdouble kmin;
  gdouble kmax;
  NcmModelCtrl *ctrl;
};

GType ncm_powspec_get_type (void) G_GNUC_CONST;

NcmPowspec *ncm_powspec_ref (NcmPowspec *powspec);
void ncm_powspec_free (NcmPowspec *powspec);
void ncm_powspec_clear (NcmPowspec **powspec);

void ncm_powspec_set_zi (NcmPowspec *powspec, const gdouble zi);
void ncm_powspec_set_zf (NcmPowspec *powspec, const gdouble zf);

void ncm_powspec_set_kmin (NcmPowspec *powspec, const gdouble kmin);
void ncm_powspec_set_kmax (NcmPowspec *powspec, const gdouble kmax);

G_INLINE_FUNC void ncm_powspec_prepare (NcmPowspec *powspec, NcmModel *model);
G_INLINE_FUNC void ncm_powspec_prepare_if_needed (NcmPowspec *powspec, NcmModel *model);
G_INLINE_FUNC gdouble ncm_powspec_eval (NcmPowspec *powspec, NcmModel *model, const gdouble z, const gdouble k);

G_END_DECLS

#endif /* _NCM_POWSPEC_H_ */


#ifndef _NCM_POWSPEC_INLINE_H_
#define _NCM_POWSPEC_INLINE_H_
#ifdef NUMCOSMO_HAVE_INLINE

G_BEGIN_DECLS

G_INLINE_FUNC void 
ncm_powspec_prepare (NcmPowspec *powspec, NcmModel *model)
{
  NCM_POWSPEC_GET_CLASS (powspec)->prepare (powspec, model);
}

G_INLINE_FUNC void
ncm_powspec_prepare_if_needed (NcmPowspec *powspec, NcmModel *model)
{
  gboolean model_up = ncm_model_ctrl_update (powspec->ctrl, NCM_MODEL (model));

  if (model_up)
    ncm_powspec_prepare (powspec, model);
}

G_INLINE_FUNC gdouble 
ncm_powspec_eval (NcmPowspec *powspec, NcmModel *model, const gdouble z, const gdouble k)
{
  return NCM_POWSPEC_GET_CLASS (powspec)->eval (powspec, model, z, k);
}

G_END_DECLS

#endif /* NUMCOSMO_HAVE_INLINE */
#endif /* _NCM_POWSPEC_INLINE_H_ */