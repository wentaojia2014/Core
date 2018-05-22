//
// Created by Mark Kellogg on 1/3/18.
//

#include "Box3.h"

namespace Core {

  Box3::Box3() {

  }

  Box3::Box3(const Vector3Components<Real>& min, const Vector3Components<Real>& max) {
    this->setMin(min);
    this->setMax(max);
  }

  Box3::Box3(Real minX, Real minY, Real minZ, Real maxX, Real maxY, Real maxZ) {
    this->setMin(minX, minY, minZ);
    this->setMax(maxX, maxY, maxZ);
  }

  void Box3::setMin(const Vector3Components<Real>& min) {
    this->min.copy(min);
  }

  void Box3::setMin(Real x, Real y, Real z) {
    this->min.set(x, y, z);
  }

  void Box3::setMax(const Vector3Components<Real>& max) {
    this->max.copy(max);
  }

  void Box3::setMax(Real x, Real y, Real z) {
    this->max.set(x, y, z);
  }

  const Box3& Box3::operator =(const Box3& other) {
    if (this == &other) return *this;
    this->min = other.min;
    this->max = other.max;
    /*this->setMin(other.min);
    this->setMax(other.max);*/
    return *this;
  }

  const Vector3r& Box3::getMin() const {
    return this->min;
  }

  const Vector3r& Box3::getMax() const {
    return this->max;
  }

  Bool Box3::containsBox(const Box3& box) const {

    return  box.min.x >= this->min.x && box.min.y >= this->min.y && box.min.z >= this->min.z &&
            box.max.x <= this->max.x && box.max.y <= this->max.y && box.max.z <= this->max.z;
  }

}

