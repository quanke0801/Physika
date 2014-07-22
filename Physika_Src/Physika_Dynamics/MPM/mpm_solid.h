/*
 * @file mpm_solid.h 
 * @Brief MPM driver used to simulate solid.
 * @author Fei Zhu
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013 Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#ifndef PHYSIKA_DYNAMICS_MPM_MPM_SOLID_H_
#define PHYSIKA_DYNAMICS_MPM_MPM_SOLID_H_

#include <vector>
#include <string>
#include "Physika_Dynamics/Driver/driver_base.h"

namespace Physika{

template<typename Scalar> class DriverPluginBase;
template<typename Scalar,int Dim> class SolidParticle;

template <typename Scalar, int Dim>
class MPMSolid: public DriverBase<Scalar>
{
public:
    MPMSolid();
    MPMSolid(unsigned int start_frame, unsigned int end_frame, Scalar frame_rate, Scalar max_dt, bool write_to_file);
    virtual ~MPMSolid();

    //virtual methods
    virtual void initConfiguration(const std::string &file_name)=0;
    virtual void advanceStep(Scalar dt)=0;
    virtual Scalar computeTimeStep()=0;
    virtual void addPlugin(DriverPluginBase<Scalar> *plugin)=0;
    virtual bool withRestartSupport() const=0;
    virtual void write(const std::string &file_name)=0;
    virtual void read(const std::string &file_name)=0;

    //get && set simulation particle data
    //virtual methods need to be overwritten in driver subclasses where inherited particles are used
    unsigned int particleNum() const;
    virtual void addParticle(const SolidParticle<Scalar,Dim> &particle);
    void removeParticle(unsigned int particle_idx);
    virtual void setParticles(const std::vector<SolidParticle<Scalar,Dim>*> &particles); //set all simulation particles, data are copied
    virtual const SolidParticle<Scalar,Dim>& particle(unsigned int particle_idx) const;
    virtual SolidParticle<Scalar,Dim>& particle(unsigned int particle_idx);

protected:
    virtual void initialize()=0;
protected:
    std::vector<SolidParticle<Scalar,Dim>*> particles_;
};

}  //end of namespace Physika

#endif //PHYSIKA_DYNAMICS_MPM_MPM_SOLID_H_