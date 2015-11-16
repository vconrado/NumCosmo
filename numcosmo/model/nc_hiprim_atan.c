/***************************************************************************
 *            nc_hiprim_atan.c
 *
 *  Thu October 29 15:14:14 2015
 *  Copyright  2015  Sandro Dias Pinto Vitenti
 *  <sandro@isoftware.com.br>
 ****************************************************************************/
/*
 * nc_hiprim_atan.c
 * Copyright (C) 2015 Sandro Dias Pinto Vitenti <sandro@isoftware.com.br>
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

/**
 * SECTION:nc_hiprim_atan
 * @title: NcHIPrimAtan
 * @short_description: Arctangent modification of the power law primordial spectrum
 *
 * This object implement the arctangent modification of the power law primordial
 * spectrum inspired in the quantum equilibrium models.
 * See:
 * - [Valentini (2010)][XValentini2010]
 * - [Colin (2015)][XColin2015]
 * - [Underwood (2015)][XUnderwood2015]
 * - [Valentini (2015)][XValentini2015]
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif /* HAVE_CONFIG_H */
#include "build_cfg.h"

#include "nc_hiprim_atan.h"

G_DEFINE_TYPE (NcHIPrimAtan, nc_hiprim_atan, NC_TYPE_HIPRIM);

enum {
  PROP_0,
  PROP_SIZE,
};

static void
nc_hiprim_atan_init (NcHIPrimAtan *prim_atan)
{
}

static void
nc_hiprim_atan_finalize (GObject *object)
{

  /* Chain up : end */
  G_OBJECT_CLASS (nc_hiprim_atan_parent_class)->finalize (object);
}

static gdouble _nc_hiprim_atan_lnSA_powespec_lnk (NcHIPrim *prim, const gdouble lnk);

static void
nc_hiprim_atan_class_init (NcHIPrimAtanClass *klass)
{
  GObjectClass* object_class = G_OBJECT_CLASS (klass);
  NcHIPrimClass *prim_class  = NC_HIPRIM_CLASS (klass);
  NcmModelClass *model_class = NCM_MODEL_CLASS (klass);

  object_class->finalize = nc_hiprim_atan_finalize;

  ncm_model_class_set_name_nick (model_class, "Atan model for primordial spectra", "Atan");
  ncm_model_class_add_params (model_class, NC_HIPRIM_ATAN_SPARAM_LEN, 0, PROP_SIZE);

  /* Set ln10e10ASA param info */
  ncm_model_class_set_sparam (model_class, NC_HIPRIM_ATAN_LN10E10ASA, "\\log(10^{10}A_{SA})", "ln10e10ASA",
                              0.0, 5.0, 1.0e-1,
                              NC_HIPRIM_DEFAULT_PARAMS_ABSTOL, NC_HIPRIM_ATAN_DEFAULT_LN10E10ASA,
                              NCM_PARAM_TYPE_FIXED);

  /* Set N_SA param info */
  ncm_model_class_set_sparam (model_class, NC_HIPRIM_ATAN_N_SA, "n_{SA}", "n_SA",
                              0.5, 1.5, 1.0e-2,
                              NC_HIPRIM_DEFAULT_PARAMS_ABSTOL, NC_HIPRIM_ATAN_DEFAULT_N_SA,
                              NCM_PARAM_TYPE_FIXED);

  /* Set c1 param info */
  ncm_model_class_set_sparam (model_class, NC_HIPRIM_ATAN_C1, "c_1", "c1",
                              0.0, 1.0e3, 10.0,
                              NC_HIPRIM_DEFAULT_PARAMS_ABSTOL, NC_HIPRIM_ATAN_DEFAULT_C1,
                              NCM_PARAM_TYPE_FIXED);
  /* Set c2 param info */
  ncm_model_class_set_sparam (model_class, NC_HIPRIM_ATAN_C2, "c_2", "c2",
                              0.0, 50.0, 5.0,
                              NC_HIPRIM_DEFAULT_PARAMS_ABSTOL, NC_HIPRIM_ATAN_DEFAULT_C2,
                              NCM_PARAM_TYPE_FIXED);
  /* Set c3 param info */
  ncm_model_class_set_sparam (model_class, NC_HIPRIM_ATAN_C3, "c_3", "c3",
                              0.5, 1.5, 1.0e-1,
                              NC_HIPRIM_DEFAULT_PARAMS_ABSTOL, NC_HIPRIM_ATAN_DEFAULT_C3,
                              NCM_PARAM_TYPE_FIXED);

  /* Check for errors in parameters initialization */
  ncm_model_class_check_params_info (model_class);

  nc_hiprim_set_lnSA_powspec_lnk_impl (prim_class, &_nc_hiprim_atan_lnSA_powespec_lnk);
}

/**
 * nc_hiprim_atan_new: (constructor)
 *
 * FIXME
 *
 * Returns: (transfer full): FIXME
 */
NcHIPrimAtan *
nc_hiprim_atan_new (void)
{
  NcHIPrimAtan *prim_pl = g_object_new (NC_TYPE_HIPRIM_ATAN,
                                            NULL);
  return prim_pl;
}

#define VECTOR     (NCM_MODEL (prim)->params)
#define LN10E10ASA (ncm_vector_get (VECTOR, NC_HIPRIM_ATAN_LN10E10ASA))
#define N_SA       (ncm_vector_get (VECTOR, NC_HIPRIM_ATAN_N_SA))
#define C1         (ncm_vector_get (VECTOR, NC_HIPRIM_ATAN_C1))
#define C2         (ncm_vector_get (VECTOR, NC_HIPRIM_ATAN_C2))
#define C3         (ncm_vector_get (VECTOR, NC_HIPRIM_ATAN_C3))

/****************************************************************************
 * Power spectrum
 ****************************************************************************/

static gdouble
_nc_hiprim_atan_lnSA_powespec_lnk (NcHIPrim *prim, const gdouble lnk)
{
  const gdouble ln_ka = lnk - prim->lnk_pivot;
  const gdouble ka = exp (ln_ka);
  const gdouble c1 = C1;
  const gdouble c2 = C2;
  const gdouble c3 = C3;
  const gdouble pi_2      = M_PI * 0.5;
  const gdouble pi_2_m_c3 = pi_2 - c3;
  const gdouble tc2       = c2 + tan (pi_2_m_c3);

  const gdouble atan_fac    = atan2 (c1 * ka + tc2, 1.0) - pi_2_m_c3;
  const gdouble ln_atan_fac = log (atan_fac);

  return (N_SA - 1.0) * ln_ka + LN10E10ASA - 10.0 * M_LN10 + ln_atan_fac;
}