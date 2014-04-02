/*
 * @file vector_3d.cpp 
 * @brief 3d vector.
 * @author Sheng Yang, Fei Zhu
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013 Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#include <cmath>
#include <limits>
#include "Physika_Core/Utilities/physika_assert.h"
#include "Physika_Core/Vectors/vector_3d.h"

namespace Physika{

template <typename Scalar>
Vector<Scalar,3>::Vector()
{
}

template <typename Scalar>
Vector<Scalar,3>::Vector(Scalar x, Scalar y, Scalar z)
{
#ifdef PHYSIKA_USE_EIGEN_VECTOR
    eigen_vector_3x_(0)=x;
    eigen_vector_3x_(1)=y;
    eigen_vector_3x_(2)=z;
#elif defined(PHYSIKA_USE_BUILT_IN_VECTOR)
    data_[0]=x;
    data_[1]=y;
    data_[2]=z;
#endif
}

template <typename Scalar>
Vector<Scalar,3>::Vector(Scalar x)
{
#ifdef PHYSIKA_USE_EIGEN_VECTOR
    eigen_vector_3x_(0)=x;
    eigen_vector_3x_(1)=x;
    eigen_vector_3x_(2)=x;
#elif defined(PHYSIKA_USE_BUILT_IN_VECTOR)
    data_[0]=data_[1]=data_[2]=x;
#endif
}

template <typename Scalar>
Vector<Scalar,3>::Vector(const Vector<Scalar,3> &vec3)
{
    *this = vec3;
}

template <typename Scalar>
Vector<Scalar,3>::~Vector()
{
}

template <typename Scalar>
Scalar& Vector<Scalar,3>::operator[] (int idx)
{
    PHYSIKA_ASSERT(idx>=0&&idx<(*this).dims());
#ifdef PHYSIKA_USE_EIGEN_VECTOR
    return eigen_vector_3x_(idx);
#elif defined(PHYSIKA_USE_BUILT_IN_VECTOR)
    return data_[idx];
#endif
}

template <typename Scalar>
const Scalar& Vector<Scalar,3>::operator[] (int idx) const
{
    PHYSIKA_ASSERT(idx>=0&&idx<(*this).dims());
#ifdef PHYSIKA_USE_EIGEN_VECTOR
    return eigen_vector_3x_(idx);
#elif defined(PHYSIKA_USE_BUILT_IN_VECTOR)
    return data_[idx];
#endif
}

template <typename Scalar>
Vector<Scalar,3> Vector<Scalar,3>::operator+ (const Vector<Scalar,3> &vec3) const
{
    Scalar result[3];
    for(int i = 0; i < 3; ++i)
        result[i] = (*this)[i] + vec3[i];
    return Vector<Scalar,3>(result[0],result[1],result[2]);
}

template <typename Scalar>
Vector<Scalar,3>& Vector<Scalar,3>::operator+= (const Vector<Scalar,3> &vec3)
{
    for(int i = 0; i < 3; ++i)
        (*this)[i] = (*this)[i] + vec3[i];
    return *this;
}

template <typename Scalar>
Vector<Scalar,3> Vector<Scalar,3>::operator- (const Vector<Scalar,3> &vec3) const
{
    Scalar result[3];
    for(int i = 0; i < 3; ++i)
        result[i] = (*this)[i] - vec3[i];
    return Vector<Scalar,3>(result[0],result[1],result[2]);
}

template <typename Scalar>
Vector<Scalar,3>& Vector<Scalar,3>::operator-= (const Vector<Scalar,3> &vec3)
{
    for(int i = 0; i < 3; ++i)
        (*this)[i] = (*this)[i] - vec3[i];
    return *this;
}

template <typename Scalar>
Vector<Scalar,3>& Vector<Scalar,3>::operator= (const Vector<Scalar,3> &vec3)
{
    for(int i = 0; i < 3; ++i)
        (*this)[i] = vec3[i];
    return *this;
}

template <typename Scalar>
bool Vector<Scalar,3>::operator== (const Vector<Scalar,3> &vec3) const
{
    for(int i = 0; i < 3; ++i)
        if((*this)[i] != vec3[i])
            return false;
    return true;
}

template <typename Scalar>
Vector<Scalar,3> Vector<Scalar,3>::operator* (Scalar scale) const
{
    Scalar result[3];
    for(int i = 0; i < 3; ++i)
        result[i] = (*this)[i] * scale;
    return Vector<Scalar,3>(result[0],result[1],result[2]);
}

template <typename Scalar>
Vector<Scalar,3>& Vector<Scalar,3>::operator*= (Scalar scale)
{
    for(int i = 0; i < 3; ++i)
        (*this)[i] = (*this)[i] * scale;
    return *this;
}

template <typename Scalar>
Vector<Scalar,3> Vector<Scalar,3>::operator/ (Scalar scale) const
{
    PHYSIKA_ASSERT(fabs(scale)>std::numeric_limits<Scalar>::epsilon());
    Scalar result[3];
    for(int i = 0; i < 3; ++i)
        result[i] = (*this)[i] / scale;
    return Vector<Scalar,3>(result[0],result[1],result[2]);
}

template <typename Scalar>
Vector<Scalar,3>& Vector<Scalar,3>::operator/= (Scalar scale)
{
    PHYSIKA_ASSERT(fabs(scale)>std::numeric_limits<Scalar>::epsilon());
    for(int i = 0; i < 3; ++i)
        (*this)[i] = (*this)[i] / scale;
    return *this;
}

template <typename Scalar>
Scalar Vector<Scalar,3>::norm() const
{
    Scalar result = (*this)[0]*(*this)[0] + (*this)[1]*(*this)[1] + (*this)[2]*(*this)[2];
    result = sqrt(result);
    return result;
}

template <typename Scalar>
Vector<Scalar,3>& Vector<Scalar,3>::normalize()
{
    Scalar norm = (*this).norm();
    bool nonzero_norm = norm > std::numeric_limits<Scalar>::epsilon();
    if(nonzero_norm)
    {
        for(int i = 0; i < 3; ++i)
        (*this)[i] = (*this)[i] / norm;
    }
    return *this;
}

template <typename Scalar>
Vector<Scalar,3> Vector<Scalar,3>::cross(const Vector<Scalar,3>& vec3) const
{
    return Vector<Scalar,3>((*this)[1]*vec3[2] - (*this)[2]*vec3[1], (*this)[2]*vec3[0] - (*this)[0]*vec3[2], (*this)[0]*vec3[1] - (*this)[1]*vec3[0]); 
}

template <typename Scalar>
Vector<Scalar,3> Vector<Scalar,3>::operator-(void) const
{
    return Vector<Scalar,3>(-(*this)[0],-(*this)[1],-(*this)[2]);
}

template <typename Scalar>
Scalar Vector<Scalar,3>::dot(const Vector<Scalar,3>& vec3) const
{
    return (*this)[0]*vec3[0] + (*this)[1]*vec3[1] + (*this)[2]*vec3[2];
}


//explicit instantiation of template so that it could be compiled into a lib
template class Vector<float,3>;
template class Vector<double,3>;

} //end of namespace Physika
