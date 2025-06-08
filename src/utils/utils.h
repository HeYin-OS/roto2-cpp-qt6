//
// Created by 12544 on 25-5-20.
//

#ifndef ROTO_2_CPP_UTILS_H
#define ROTO_2_CPP_UTILS_H

#include "../macros.h"
#include "../data/CurveUtils.h"

namespace roto_util {
    template<typename T>
    void bezier_curve_linear_interpolation(T itr_begin, T itr_end, const int i_start, const int i_end) {
        // 容器大小
        auto container_size = std::distance(itr_begin, itr_end);
        // 超出容器边界
        if (i_start > container_size - 1 || i_end > container_size - 1) return;
        // 线性插值个数
        auto n = i_end - i_start - 1;
        // 插值起始点
        auto p_start = std::next(itr_begin, i_start);
        // 插值终点
        auto p_end = std::next(itr_begin, i_end);
        // 控制点个数
        auto n_points = (*p_start).getPointCount();
        // 全部待插值曲线
        for (auto i = 1; i <= n; i++) {
            // 当前贝塞尔曲线
            auto p = std::next(p_start, i);
            p->resizeControlPoints(n_points);
            // 全部曲线点
            for (auto j = 0; j < n_points; j++) {
                auto [x0, y0] = (*p_start)[j];
                auto [x1, y1] = (*p_end)[j];
                double t = static_cast<double>(i) / n;
                (*p)[j] = {(1.f - t) * x0 + t * x1, (1.f - t) * y0 + t * y1};
            }
        }
    }
}


#endif //ROTO_2_CPP_UTILS_H
