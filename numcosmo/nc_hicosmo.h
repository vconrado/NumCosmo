/***************************************************************************
 *            nc_hicosmo.h
 *
 *  Mon Jul 16 18:03:42 2007
 *  Copyright  2007  Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * numcosmo
 * Copyright (C) Sandro Dias Pinto Vitenti 2012 <sandro@isoftware.com.br>
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

#ifndef _NC_HICOSMO_H_
#define _NC_HICOSMO_H_

#include <glib.h>
#include <glib-object.h>
#include <numcosmo/build_cfg.h>
#include <numcosmo/math/ncm_c.h>
#include <numcosmo/math/ncm_model.h>
#include <numcosmo/math/ncm_mset_func.h>
#include <numcosmo/math/ncm_likelihood.h>

G_BEGIN_DECLS

#define NC_TYPE_HICOSMO             (nc_hicosmo_get_type ())
#define NC_HICOSMO(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), NC_TYPE_HICOSMO, NcHICosmo))
#define NC_HICOSMO_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), NC_TYPE_HICOSMO, NcHICosmoClass))
#define NC_IS_HICOSMO(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NC_TYPE_HICOSMO))
#define NC_IS_HICOSMO_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), NC_TYPE_HICOSMO))
#define NC_HICOSMO_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), NC_TYPE_HICOSMO, NcHICosmoClass))

/**
 * NcHICosmoImpl:
 * @NC_HICOSMO_IMPL_H0: Hubble constant
 * @NC_HICOSMO_IMPL_Omega_b: Baryonic density today $\Omega_b$
 * @NC_HICOSMO_IMPL_Omega_g: Photons density today $\Omega_\gamma$
 * @NC_HICOSMO_IMPL_Omega_nu: Ultra-relativistic neutrinos density today $\Omega_\nu$
 * @NC_HICOSMO_IMPL_Omega_r: Radiation density today $\Omega_r$
 * @NC_HICOSMO_IMPL_Omega_c: Cold dark matter density today $\Omega_c$
 * @NC_HICOSMO_IMPL_Omega_t: Total density today $\Omega_t$
 * @NC_HICOSMO_IMPL_sigma_8: Standard deviation of the matter density contrast at scale $R = 8h^{-1} \text{Mpc}$, $\sigma_8$
 * @NC_HICOSMO_IMPL_T_gamma0: Radiation temperature today
 * @NC_HICOSMO_IMPL_Yp_4He: Primordial Helium mass fraction 
 * @NC_HICOSMO_IMPL_z_lss: Redshift of the last scatering surface
 * @NC_HICOSMO_IMPL_as_drag: Acoustic Scale at drag redshift
 * @NC_HICOSMO_IMPL_xb: Maximum redshift
 * @NC_HICOSMO_IMPL_E2: Adimensional Hubble function squared
 * @NC_HICOSMO_IMPL_dE2_dz: Derivative of the dimensionless Hubble function squared.
 * @NC_HICOSMO_IMPL_d2E2_dz2: Second derivative of the dimensionless Hubble function squared.
 * @NC_HICOSMO_IMPL_cs2: Speed of sound squared.
 * @NC_HICOSMO_IMPL_rhopp: energy density plus pressure.
 * @NC_HICOSMO_IMPL_cd: Comoving distance
 * @NC_HICOSMO_IMPL_powspec: Perturbations power spectrum
 *
 * FIXME
 */
typedef enum _NcHICosmoImpl
{
  NC_HICOSMO_IMPL_H0              = 1 << 0,
  NC_HICOSMO_IMPL_Omega_b         = 1 << 1,
  NC_HICOSMO_IMPL_Omega_g         = 1 << 2,
  NC_HICOSMO_IMPL_Omega_nu        = 1 << 3,
  NC_HICOSMO_IMPL_Omega_r         = 1 << 4,
  NC_HICOSMO_IMPL_Omega_c         = 1 << 5,
  NC_HICOSMO_IMPL_Omega_t         = 1 << 6,
  NC_HICOSMO_IMPL_sigma_8         = 1 << 7,
  NC_HICOSMO_IMPL_T_gamma0        = 1 << 8,
  NC_HICOSMO_IMPL_Yp_4He           = 1 << 9,
  NC_HICOSMO_IMPL_z_lss           = 1 << 10,
  NC_HICOSMO_IMPL_as_drag         = 1 << 11,
  NC_HICOSMO_IMPL_xb              = 1 << 12,
  NC_HICOSMO_IMPL_E2              = 1 << 13,
  NC_HICOSMO_IMPL_dE2_dz          = 1 << 14,
  NC_HICOSMO_IMPL_d2E2_dz2        = 1 << 15,
  NC_HICOSMO_IMPL_cs2             = 1 << 16,
  NC_HICOSMO_IMPL_rhopp           = 1 << 17,
  NC_HICOSMO_IMPL_cd              = 1 << 18,
  NC_HICOSMO_IMPL_powspec         = 1 << 19, /*< private >*/
  NC_HICOSMO_IMPL_LAST            = 1 << 23, /*< skip >*/
} NcHICosmoImpl;

#define NC_HICOSMO_IMPL_RH_Mpc (NC_HICOSMO_IMPL_H0)
#define NC_HICOSMO_IMPL_Omega_k (NC_HICOSMO_IMPL_Omega_t)
#define NC_HICOSMO_IMPL_Omega_m (NC_HICOSMO_IMPL_Omega_c | NC_HICOSMO_IMPL_Omega_b)
#define NC_HICOSMO_IMPL_h (NC_HICOSMO_IMPL_H0)
#define NC_HICOSMO_IMPL_h2 (NC_HICOSMO_IMPL_H0)
#define NC_HICOSMO_IMPL_Omega_bh2 (NC_HICOSMO_IMPL_Omega_b | NC_HICOSMO_IMPL_h2)
#define NC_HICOSMO_IMPL_Omega_gh2 (NC_HICOSMO_IMPL_Omega_g | NC_HICOSMO_IMPL_h2)
#define NC_HICOSMO_IMPL_Omega_nuh2 (NC_HICOSMO_IMPL_Omega_nu | NC_HICOSMO_IMPL_h2)
#define NC_HICOSMO_IMPL_Omega_ch2 (NC_HICOSMO_IMPL_Omega_c | NC_HICOSMO_IMPL_h2)
#define NC_HICOSMO_IMPL_Omega_rh2 (NC_HICOSMO_IMPL_Omega_r | NC_HICOSMO_IMPL_h2)
#define NC_HICOSMO_IMPL_Omega_mh2 (NC_HICOSMO_IMPL_Omega_m | NC_HICOSMO_IMPL_h2)
#define NC_HICOSMO_IMPL_H_Yp (NC_HICOSMO_IMPL_Yp_4He)
#define NC_HICOSMO_IMPL_XHe (NC_HICOSMO_IMPL_Yp_4He)

#define NC_HICOSMO_IMPL_H (NC_HICOSMO_IMPL_H0 | NC_HICOSMO_IMPL_E2)
#define NC_HICOSMO_IMPL_dH_dz (NC_HICOSMO_IMPL_H0 | NC_HICOSMO_IMPL_E2 | NC_HICOSMO_IMPL_dE2_dz)
#define NC_HICOSMO_IMPL_E (NC_HICOSMO_IMPL_E2)
#define NC_HICOSMO_IMPL_Em2 (NC_HICOSMO_IMPL_E2)
#define NC_HICOSMO_IMPL_q (NC_HICOSMO_IMPL_E2 | NC_HICOSMO_IMPL_dE2_dz)
#define NC_HICOSMO_IMPL_j (NC_HICOSMO_IMPL_E2 | NC_HICOSMO_IMPL_dE2_dz | NC_HICOSMO_IMPL_d2E2_dz2)
#define NC_HICOSMO_IMPL_Omega_k (NC_HICOSMO_IMPL_Omega_t)
#define NC_HICOSMO_IMPL_wec (NC_HICOSMO_IMPL_E2 | NC_HICOSMO_IMPL_Omega_k)
#define NC_HICOSMO_IMPL_dec (NC_HICOSMO_IMPL_E2 | NC_HICOSMO_IMPL_Omega_k)

typedef struct _NcHICosmoClass NcHICosmoClass;
typedef struct _NcHICosmo NcHICosmo;
typedef gdouble (*NcHICosmoFunc0) (NcHICosmo *cosmo);
typedef gdouble (*NcHICosmoFunc1) (NcHICosmo *cosmo, gdouble x);

/**
 * NcHICosmo:
 *
 * FIXME
 *
 */
struct _NcHICosmo
{
  /*< private >*/
  NcmModel parent_instance;
  gboolean is_eternal;
};

typedef struct _NcHICosmoFuncZ
{
  const gchar *name;
  const gchar *desc;
  NcHICosmoFunc1 f;
  NcHICosmoImpl impl;
} NcHICosmoFuncZ;

typedef struct _NcHICosmoFunc
{
  const gchar *name;
  const gchar *desc;
  NcHICosmoFunc0 f;
  NcHICosmoImpl impl;
} NcHICosmoFunc;

struct _NcHICosmoClass
{
  /*< private >*/
  NcmModelClass parent_class;
  NcHICosmoFunc0 H0;
  NcHICosmoFunc0 Omega_b;
  NcHICosmoFunc0 Omega_g;
  NcHICosmoFunc0 Omega_nu;
  NcHICosmoFunc0 Omega_r;
  NcHICosmoFunc0 Omega_c;
  NcHICosmoFunc0 Omega_t;
  NcHICosmoFunc0 sigma_8;
  NcHICosmoFunc0 T_gamma0;
  NcHICosmoFunc0 Yp_4He;
  NcHICosmoFunc0 z_lss;
  NcHICosmoFunc0 as_drag;
  NcHICosmoFunc0 xb;
  NcHICosmoFunc1 E2;
  NcHICosmoFunc1 dE2_dz;
  NcHICosmoFunc1 d2E2_dz2;
  NcHICosmoFunc1 cs2;
  NcHICosmoFunc1 rhopp;
  NcHICosmoFunc1 cd;
  NcHICosmoFunc1 powspec;
  GArray *func_table;
  GArray *func_z_table;
  GHashTable *func_hash;
  GHashTable *func_z_hash;
};

GType nc_hicosmo_get_type (void) G_GNUC_CONST;

NCM_MSET_MODEL_DECLARE_ID (nc_hicosmo);

/*
 * Cosmological model constant functions
 */
G_INLINE_FUNC gdouble nc_hicosmo_H0 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_b (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_g (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_nu (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_r (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_c (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_t (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_T_gamma0 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Yp_4He (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_sigma_8 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_z_lss (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_as_drag (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_xb (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_E2 (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_dE2_dz (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_d2E2_dz2 (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_cs2 (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_rhopp (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_cd (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_powspec (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_RH_Mpc (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_k (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_m (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_h (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_h2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_bh2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_gh2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_nuh2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_ch2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_rh2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Omega_mh2 (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_Yp_1H (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_XHe (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_crit_density (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_baryon_density (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_He_number_density (NcHICosmo *cosmo);
G_INLINE_FUNC gdouble nc_hicosmo_H_number_density (NcHICosmo *cosmo);

G_INLINE_FUNC gdouble nc_hicosmo_E (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_Em2 (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_H (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_dH_dz (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_j (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_qp (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_q (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_dec (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_wec (NcHICosmo *cosmo, gdouble z);
G_INLINE_FUNC gdouble nc_hicosmo_abs_alpha (NcHICosmo *cosmo, gdouble x);
G_INLINE_FUNC gdouble nc_hicosmo_x_alpha (NcHICosmo *cosmo, gdouble alpha);

GArray *nc_hicosmo_class_func_table (void);
GArray *nc_hicosmo_class_func_z_table (void);
NcHICosmoFunc *nc_hicosmo_class_get_func (const gchar *name);
NcHICosmoFuncZ *nc_hicosmo_class_get_func_z (const gchar *name);

NcHICosmo *nc_hicosmo_new_from_name (GType parent_type, gchar *cosmo_name);
NcHICosmo *nc_hicosmo_ref (NcHICosmo *cosmo);
void nc_hicosmo_free (NcHICosmo *cosmo);
void nc_hicosmo_clear (NcHICosmo **cosmo);

void nc_hicosmo_log_all_models (GType parent);

NcmMSetFunc *nc_hicosmo_create_mset_func0 (NcHICosmoFunc0 f0);
NcmMSetFunc *nc_hicosmo_create_mset_func1 (NcHICosmoFunc1 f1);
NcmMSetFunc *nc_hicosmo_create_mset_arrayfunc1 (NcHICosmoFunc1 f1, guint size);

void nc_hicosmo_set_H0_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Omega_b_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Omega_g_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Omega_nu_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Omega_r_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Omega_c_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Omega_t_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_sigma_8_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_T_gamma0_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_Yp_4He_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_z_lss_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_as_drag_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);
void nc_hicosmo_set_xb_impl (NcHICosmoClass *model_class, NcHICosmoFunc0 f);

void nc_hicosmo_set_E2_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);
void nc_hicosmo_set_dE2_dz_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);
void nc_hicosmo_set_d2E2_dz2_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);
void nc_hicosmo_set_cs2_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);
void nc_hicosmo_set_rhopp_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);
void nc_hicosmo_set_cd_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);
void nc_hicosmo_set_powspec_impl (NcHICosmoClass *model_class, NcHICosmoFunc1 f);

#define NC_HICOSMO_DEFAULT_PARAMS_RELTOL (1e-7)
#define NC_HICOSMO_DEFAULT_PARAMS_ABSTOL (0.0)

G_END_DECLS

#endif /* _NC_HICOSMO_H_ */

#ifndef _NC_HICOSMO_INLINE_H_
#define _NC_HICOSMO_INLINE_H_
#ifdef NUMCOSMO_HAVE_INLINE

G_BEGIN_DECLS

NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,H0)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Omega_b)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Omega_g)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Omega_nu)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Omega_r)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Omega_c)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Omega_t)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,T_gamma0)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,Yp_4He)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,sigma_8)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,z_lss)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,as_drag)
NCM_MODEL_FUNC0_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,xb)

NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,E2)
NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,dE2_dz)
NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,d2E2_dz2)
NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,cs2)
NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,rhopp)
NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,cd)
NCM_MODEL_FUNC1_IMPL (NC_HICOSMO,NcHICosmo,nc_hicosmo,powspec)

G_INLINE_FUNC gdouble
nc_hicosmo_RH_Mpc (NcHICosmo *cosmo)
{
  return (ncm_c_c () / (1.0e3 * nc_hicosmo_H0 (cosmo)));
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_k (NcHICosmo *cosmo)
{
  return (1.0 - nc_hicosmo_Omega_t (cosmo));
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_m (NcHICosmo *cosmo)
{
  return (nc_hicosmo_Omega_b (cosmo) + nc_hicosmo_Omega_c (cosmo));
}

G_INLINE_FUNC gdouble
nc_hicosmo_H (NcHICosmo *cosmo, gdouble z)
{
  return (nc_hicosmo_H0 (cosmo) * sqrt (nc_hicosmo_E2 (cosmo, z)));
}

G_INLINE_FUNC gdouble
nc_hicosmo_h (NcHICosmo *cosmo)
{
  return nc_hicosmo_H0 (cosmo) / 100.0;
}

G_INLINE_FUNC gdouble
nc_hicosmo_h2 (NcHICosmo *cosmo)
{
  return gsl_pow_2 (nc_hicosmo_H0 (cosmo) / 100.0);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_bh2 (NcHICosmo *cosmo)
{
  return nc_hicosmo_h2 (cosmo) * nc_hicosmo_Omega_b (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_gh2 (NcHICosmo *cosmo)
{
  return nc_hicosmo_h2 (cosmo) * nc_hicosmo_Omega_g (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_nuh2 (NcHICosmo *cosmo)
{
  return nc_hicosmo_h2 (cosmo) * nc_hicosmo_Omega_nu (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_ch2 (NcHICosmo *cosmo)
{
  return nc_hicosmo_h2 (cosmo) * nc_hicosmo_Omega_c (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_rh2 (NcHICosmo *cosmo)
{
  return nc_hicosmo_h2 (cosmo) * nc_hicosmo_Omega_r (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Omega_mh2 (NcHICosmo *cosmo)
{
  return nc_hicosmo_h2 (cosmo) * nc_hicosmo_Omega_m (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_Yp_1H (NcHICosmo *cosmo)
{
  return 1.0 - nc_hicosmo_Yp_4He (cosmo);
}

G_INLINE_FUNC gdouble
nc_hicosmo_XHe (NcHICosmo *cosmo)
{
  return nc_hicosmo_Yp_4He (cosmo) / (ncm_c_mass_ratio_4He_1H () * nc_hicosmo_Yp_1H (cosmo));
}

G_INLINE_FUNC gdouble 
nc_hicosmo_crit_density (NcHICosmo *cosmo)
{
  const gdouble h2 = nc_hicosmo_h2 (cosmo);
  return ncm_c_crit_density_h2 () * h2;
}

G_INLINE_FUNC gdouble 
nc_hicosmo_baryon_density (NcHICosmo *cosmo)
{
  const gdouble rho_crit = nc_hicosmo_crit_density (cosmo);
  const gdouble Omega_b  = nc_hicosmo_Omega_b (cosmo);
  const gdouble rho_b0   = Omega_b * rho_crit;

  return rho_b0;
}

G_INLINE_FUNC gdouble 
nc_hicosmo_He_number_density (NcHICosmo *cosmo)
{
  const gdouble rho_b0 = nc_hicosmo_baryon_density (cosmo);
  const gdouble Yp_4He  = nc_hicosmo_Yp_4He (cosmo);
  const gdouble E_4He  = ncm_c_rest_energy_4He ();

  return Yp_4He * rho_b0 / E_4He;
}

G_INLINE_FUNC gdouble 
nc_hicosmo_H_number_density (NcHICosmo *cosmo)
{
  const gdouble rho_b0 = nc_hicosmo_baryon_density (cosmo);
  const gdouble Yp_1H  = nc_hicosmo_Yp_1H (cosmo);
  const gdouble E_1H   = ncm_c_rest_energy_1H ();

  return Yp_1H * rho_b0 / E_1H;
}

G_INLINE_FUNC gdouble
nc_hicosmo_E (NcHICosmo *cosmo, gdouble z)
{
  return sqrt (nc_hicosmo_E2 (cosmo, z));
}

G_INLINE_FUNC gdouble
nc_hicosmo_Em2 (NcHICosmo *cosmo, gdouble z)
{
  return 1.0 / nc_hicosmo_E2 (cosmo, z);
}

G_INLINE_FUNC gdouble
nc_hicosmo_dH_dz (NcHICosmo *cosmo, gdouble z)
{
  return nc_hicosmo_H0 (cosmo) *
	nc_hicosmo_dE2_dz (cosmo, z) / (2.0 * sqrt (nc_hicosmo_E2 (cosmo, z)));
}

G_INLINE_FUNC gdouble
nc_hicosmo_q (NcHICosmo *cosmo, gdouble z)
{
  gdouble E2, dE2_dz;
  E2 = nc_hicosmo_E2 (cosmo, z);
  dE2_dz = nc_hicosmo_dE2_dz (cosmo, z);
  return (dE2_dz * (1.0 + z) / (2.0 * E2) - 1.0);
}

G_INLINE_FUNC gdouble
nc_hicosmo_dec (NcHICosmo *cosmo, gdouble z)
{
  gdouble q, E2, Ok;
  gdouble x = 1.0 + z;
  q = nc_hicosmo_q (cosmo, z);
  E2 = nc_hicosmo_E2 (cosmo, z);
  Ok = nc_hicosmo_Omega_k (cosmo);

  return (2.0 * E2 - q * E2 - 2.0 * Ok * x * x) / 3.0;
}

G_INLINE_FUNC gdouble
nc_hicosmo_wec (NcHICosmo *cosmo, gdouble z)
{
  gdouble E2, Ok;
  gdouble x = 1.0 + z;
  E2 = nc_hicosmo_E2 (cosmo, z);
  Ok = nc_hicosmo_Omega_k (cosmo);

  return (E2 - Ok * x * x);
}

G_INLINE_FUNC gdouble
nc_hicosmo_qp (NcHICosmo *cosmo, gdouble z)
{
  gdouble E2, dE2_dz, d2E2_dz2;
  E2 = nc_hicosmo_E2 (cosmo, z);
  dE2_dz = nc_hicosmo_dE2_dz (cosmo, z);
  d2E2_dz2 = nc_hicosmo_d2E2_dz2 (cosmo, z);

  return (1.0 + z) / (2.0 * E2) * (dE2_dz / (1.0 + z) + d2E2_dz2 - dE2_dz * dE2_dz / E2);
}

G_INLINE_FUNC gdouble
nc_hicosmo_j (NcHICosmo *cosmo, gdouble z)
{
  gdouble E2, dE2_dz, d2E2_dz2;
  E2 = nc_hicosmo_E2 (cosmo, z);
  dE2_dz = nc_hicosmo_dE2_dz (cosmo, z);
  d2E2_dz2 = nc_hicosmo_d2E2_dz2 (cosmo, z);

  return gsl_pow_2 (1.0 + z) * (d2E2_dz2 - 2.0 * dE2_dz / (1.0 + z)) / (2.0 * E2) + 1.0;
}

G_INLINE_FUNC gdouble
nc_hicosmo_x_alpha (NcHICosmo *cosmo, gdouble alpha)
{
  const gdouble xb = nc_hicosmo_xb (cosmo);
  return xb * exp (- (alpha * alpha) * 0.5);
}

G_INLINE_FUNC gdouble
nc_hicosmo_abs_alpha (NcHICosmo *cosmo, gdouble x)
{
  const gdouble xb = nc_hicosmo_xb (cosmo);
  return sqrt (2.0 * log (xb / x));
}

G_END_DECLS

#endif /* NUMCOSMO_HAVE_INLINE */
#endif /* _NC_HICOSMO_INLINE_H_ */
