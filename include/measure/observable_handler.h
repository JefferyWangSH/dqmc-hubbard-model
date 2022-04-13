#ifndef OBSERABLE_HANDLER_H
#define OBSERABLE_HANDLER_H
#pragma once

/**
  *  This header file defines the Observable::ObservableHandler class 
  *  to handle with the list of observables during dqmc simulations.
  *  Automatic classification of input observables and the allocation of memory are included.
  */

#include <map>
#include <memory>
#include "measure/observable.h"


namespace Observable {

    // --------------------- Handler class Observable::ObservableHandler ---------------------
    class ObservableHandler {
        public:

            using ObsMap = std::map<std::string, std::unique_ptr<ObservableBase>>;

            using ptrScalarObs = std::unique_ptr<ScalarObs>;
            using ptrVectorObs = std::unique_ptr<VectorObs>;
            using ptrMatrixObs = std::unique_ptr<MatrixObs>;
            
            using EqtimeScalarObs = std::vector<std::unique_ptr<ScalarObs>>;
            using EqtimeVectorObs = std::vector<std::unique_ptr<VectorObs>>;
            using EqtimeMatrixObs = std::vector<std::unique_ptr<MatrixObs>>;
            using DynamicScalarObs = std::vector<std::unique_ptr<ScalarObs>>;
            using DynamicVectorObs = std::vector<std::unique_ptr<VectorObs>>;
            using DynamicMatrixObs = std::vector<std::unique_ptr<MatrixObs>>;

            using ObsName = std::string;
            using ObsNameList = std::vector<std::string>;
            using EqtimeObsNameList = std::vector<std::string>;
            using DynamicObsNameList = std::vector<std::string>;

            // map of observables for quick reference
            // only for finding or searching cetain observable, and frequently calls should be avoided
            ObsMap m_obs_map{};

            EqtimeScalarObs m_eqtime_scalar_obs{};
            EqtimeVectorObs m_eqtime_vector_obs{};
            EqtimeMatrixObs m_eqtime_matrix_obs{};

            DynamicScalarObs m_dynamic_scalar_obs{};
            DynamicVectorObs m_dynamic_vector_obs{};
            DynamicMatrixObs m_dynamic_matrix_obs{};

            // list of supported physical observables
            EqtimeObsNameList m_eqtime_obs_name = {
                                                    "filling_number", 
                                                    "double_occupancy", 
                                                    "kinetic_energy", 
                                                    "momentum_distribution", 
                                                    "local_spin_corr", 
                                                    "spin_density_structure_factor", 
                                                    "charge_density_structure_factor", 
                                                    "s_wave_pairing_corr",
                                                    };

            DynamicObsNameList m_dynamic_obs_name = {
                                                    "greens_functions", 
                                                    "density_of_states", 
                                                    "superfluid_stiffness", 
                                                    };

        public:

            ObservableHandler() = default;

            // check if certain observable exists
            bool find(const ObsName& obs_name) ;

            // return certain type of the observable class
            const ScalarObs find_scalar(const ObsName& obs_name);
            const VectorObs find_vector(const ObsName& obs_name);
            const MatrixObs find_matrix(const ObsName& obs_name);

            // initialize the handler
            void initial(const ObsNameList& obs_list);

        private:
            // read list of observables which are to be measured
            void read_obs_list(const ObsNameList& obs_list);

            // segment input observables into two classes, equal-time and time-displaced (dynamic)
            void classify();

            // allocate Observable class according to the input list
            void allocate();

    };

} // namespace Observable


#endif // OBSERVABLE_HANDLER_H