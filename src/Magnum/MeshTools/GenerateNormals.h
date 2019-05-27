#ifndef Magnum_MeshTools_GenerateNormals_h
#define Magnum_MeshTools_GenerateNormals_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Function @ref Magnum::MeshTools::generateFlatNormals(), @ref Magnum::MeshTools::generateFlatNormalsInto(), @ref Magnum::MeshTools::generateSmoothNormals(), @ref Magnum::MeshTools::generateSmoothNormalsInto()
 */

#include "Magnum/Magnum.h"
#include "Magnum/MeshTools/visibility.h"

#ifdef MAGNUM_BUILD_DEPRECATED
#include <Corrade/Utility/StlForwardVector.h>
#include <Corrade/Utility/Macros.h>
#endif

namespace Magnum { namespace MeshTools {

/**
@brief Generate flat normals
@param positions    Triangle vertex positions
@return Per-vertex normals

All vertices in each triangle face get the same normal vector. Expects that the
position count is divisible by 3. If you need to generate flat normals for an
indexed mesh, @ref duplicate() the vertices first, after the operation you
might want to remove the duplicates again using @ref removeDuplicates().
Example usage:

@snippet MagnumMeshTools.cpp generateFlatNormals

@see @ref generateFlatNormalsInto(), @ref generateSmoothNormals()
*/
MAGNUM_MESHTOOLS_EXPORT Containers::Array<Vector3> generateFlatNormals(const Containers::StridedArrayView1D<const Vector3>& positions);

/**
@brief Generate flat normals into an existing array
@param[in]  positions   Triangle vertex positions
@param[out] normals     Where to put the generated normals

A variant of @ref generateFlatNormals() that fills existing memory instead of
allocating a new array. The @p normals array is expected to have the same size
as @p positions.
@see @ref generateSmoothNormalsInto()
*/
MAGNUM_MESHTOOLS_EXPORT void generateFlatNormalsInto(const Containers::StridedArrayView1D<const Vector3>& positions, const Containers::StridedArrayView1D<Vector3>& normals);

#ifdef MAGNUM_BUILD_DEPRECATED
/**
@brief Generate flat normals
@param indices      Triangle face indices
@param positions    Triangle vertex positions
@return Normal indices and vectors

All vertices in each triangle face get the same normal vector. Removes
duplicates before returning. Expects that the position count is divisible by 3.

@deprecated This will generate index buffer that's different from the input
    @p indices array, so you'll need to recombine them using
    @ref combineIndexedArrays() in order to have a single index array for both
    vertices and normals. Because this makes the usage more complex than
    strictly neccessary, this function is deprecated in favor of
    @ref generateFlatNormals(const Containers::StridedArrayView1D<const Vector3>&).
*/
CORRADE_DEPRECATED("use generateFlatNormals(const Containers::StridedArrayView1D<const Vector3>&) instead") std::pair<std::vector<UnsignedInt>, std::vector<Vector3>> MAGNUM_MESHTOOLS_EXPORT generateFlatNormals(const std::vector<UnsignedInt>& indices, const std::vector<Vector3>& positions);
#endif

/**
@brief Generate smooth normals
@param indices      Triangle face indices
@param positions    Triangle vertex positions
@return Per-vertex normals

Uses the @p indices array to discover adjacent triangles and then for each
vertex position calculates a normal averaged from all triangles that share it.
The normal is weighted according to adjacent triangle area and angle at given
vertex; hard edges are preserved where adjacent triangles don't share vertices.

Implementation is based on the article
[Weighted Vertex Normals](http://www.bytehazard.com/articles/vertnorm.html) by
Martijn Buijs.
@see @ref generateSmoothNormalsInto(), @ref generateFlatNormals()
*/
template<class T> MAGNUM_MESHTOOLS_EXPORT Containers::Array<Vector3> generateSmoothNormals(const Containers::StridedArrayView1D<const T>& indices, const Containers::StridedArrayView1D<const Vector3>& positions);

#if defined(CORRADE_TARGET_WINDOWS) && !defined(__MINGW32__)
extern template MAGNUM_MESHTOOLS_EXPORT Containers::Array<Vector3> generateSmoothNormals<UnsignedByte>(const Containers::StridedArrayView1D<const UnsignedByte>&, const Containers::StridedArrayView1D<const Vector3>&);
extern template MAGNUM_MESHTOOLS_EXPORT Containers::Array<Vector3> generateSmoothNormals<UnsignedShort>(const Containers::StridedArrayView1D<const UnsignedShort>&, const Containers::StridedArrayView1D<const Vector3>&);
extern template MAGNUM_MESHTOOLS_EXPORT Containers::Array<Vector3> generateSmoothNormals<UnsignedInt>(const Containers::StridedArrayView1D<const UnsignedInt>&, const Containers::StridedArrayView1D<const Vector3>&);
#endif

/**
@brief Generate smooth normals into an existing array
@param[in] indices      Triangle face indices
@param[in] positions    Triangle vertex positions
@param[out] normals     Where to put the generated normals

A variant of @ref generateSmoothNormals() that fills existing memory instead of
allocating a new array. The @p normals array is expected to have the same size
as @p positions. Note that even with the output array this function isn't fully
allocation-free --- it still allocates two additional internal arrays for
adjacent face calculation.
@see @ref generateFlatNormalsInto()
*/
template<class T> MAGNUM_MESHTOOLS_EXPORT void generateSmoothNormalsInto(const Containers::StridedArrayView1D<const T>& indices, const Containers::StridedArrayView1D<const Vector3>& positions, const Containers::StridedArrayView1D<Vector3>& normals);

#if defined(CORRADE_TARGET_WINDOWS) && !defined(__MINGW32__)
extern template MAGNUM_MESHTOOLS_EXPORT void generateSmoothNormalsInto<UnsignedByte>(const Containers::StridedArrayView1D<const UnsignedByte>&, const Containers::StridedArrayView1D<const Vector3>&, const Containers::StridedArrayView1D<Vector3>&);
extern template MAGNUM_MESHTOOLS_EXPORT void generateSmoothNormalsInto<UnsignedShort>(const Containers::StridedArrayView1D<const UnsignedShort>&, const Containers::StridedArrayView1D<const Vector3>&, const Containers::StridedArrayView1D<Vector3>&);
extern template MAGNUM_MESHTOOLS_EXPORT void generateSmoothNormalsInto<UnsignedInt>(const Containers::StridedArrayView1D<const UnsignedInt>&, const Containers::StridedArrayView1D<const Vector3>&, const Containers::StridedArrayView1D<Vector3>&);
#endif

}}

#endif
