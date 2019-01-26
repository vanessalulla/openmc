#ifndef OPENMC_TALLIES_DERIVATIVE_H
#define OPENMC_TALLIES_DERIVATIVE_H

#include <unordered_map>
#include <vector>

#include "pugixml.hpp"

//==============================================================================
//! Describes a first-order derivative that can be applied to tallies.
//==============================================================================

namespace openmc {

extern "C" struct TallyDerivative {
  int id;  //!< User-defined identifier
  int variable;  //!< Independent variable (like temperature)
  int diff_material;  //!< Material this derivative is applied to
  int diff_nuclide;  //!< Nuclide this material is applied to
  double flux_deriv;  //!< Derivative of the current particle's weight

  TallyDerivative() {}
  TallyDerivative(pugi::xml_node node);
};

} // namespace openmc

//==============================================================================
// Global variables
//==============================================================================

// Explicit vector template specialization declaration of threadprivate variable
// outside of the openmc namespace for the picky Intel compiler.
extern template class std::vector<openmc::TallyDerivative>;

namespace openmc {
  namespace model {
    extern std::vector<TallyDerivative> tally_derivs;
    #pragma omp threadprivate(tally_derivs)

    extern std::unordered_map<int, int> tally_deriv_map;
  }

  // Independent variables
  //TODO: convert to enum
  constexpr int DIFF_DENSITY {1};
  constexpr int DIFF_NUCLIDE_DENSITY {2};
  constexpr int DIFF_TEMPERATURE {3};
}

#endif // OPENMC_TALLIES_DERIVATIVE_H
