//
// Created by jwkim98 on 19. 1. 12.
//

#ifndef TAKIMATRIX_MATRIX_OBJECT_HPP
#define TAKIMATRIX_MATRIX_OBJECT_HPP

#include <cstdio>
#include <vector>

namespace TakiMatrix::processor {
    size_t matrix_object_id = 0;

    class matrix_object {
    public:
        matrix_object() = default;

        /**
         * @brief : constructor for temporary matrix_objects
         * (Not associated with matrix object in user code)
         * @param data : data for this matrix
         * @param shape : shape of the data
         */
        matrix_object(const std::vector<float>& data,
                const std::vector<size_t>& shape);

        /**
         * @brief : constructor for real matrix_objects
         * (Associated with matrix object in user code)
         * @param data : data for this matrix
         * @param shape : shape of the data
         * @param origin_id : id of user-code matrix that this matrix_object is
         * associated with
         */
        matrix_object(const std::vector<float>& data,
                const std::vector<size_t>& shape, size_t origin_id);

        matrix_object(const matrix_object& rhs);

    private:
        std::vector<float> data;
        std::vector<size_t> shape;
        /// data size in bytes
        size_t data_size = 0;
        /// unique id of this matrix_object
        size_t m_matrix_object_id;
        /// true if this object is non-temporary
        bool m_has_origin = false;
        /// id of origin matrix (if it has one)
        size_t m_origin_id = 0;
    };
} // namespace TakiMatrix::processor

#endif // TAKIMATRIX_MATRIX_HPP
