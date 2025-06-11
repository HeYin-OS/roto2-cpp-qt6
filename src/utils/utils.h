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
        const auto n = i_end - i_start - 1;
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

    inline pair<double, double> compute_coordinate_cubic_bezier(const pair<double, double> &p0, const pair<double, double> &p1, const pair<double, double> &p2, const pair<double, double> &p3, const double t) {
        // 计算系数
        const double u = 1.0 - t;
        const double b0 = u * u * u;
        const double b1 = 3 * u * u * t;
        const double b2 = 3 * u * t * t;
        const double b3 = t * t * t;
        // 计算坐标
        double x = b0 * p0.first + b1 * p1.first + b2 * p2.first + b3 * p3.first;
        double y = b0 * p0.second + b1 * p1.second + b2 * p2.second + b3 * p3.second;
        // 返回坐标
        return {x, y};
    }

    inline double distance_2d(const pair<double, double> &a, const pair<double, double> &b) {
        const double dx = a.first - b.first;
        const double dy = a.second - b.second;
        // 两点距离
        return sqrt(dx * dx + dy * dy);
    }

    inline vector<vector<double>> sample_cubic_bezier_by_pixel_length(const vector<pair<double, double>> &control_points, const double pixel_step = 1.0) {
        vector<vector<double>> all_t_values;
        // 没有贝塞尔曲线
        if (control_points.size() < 4) {
            return {};
        }
        // 遍历每组贝塞尔曲线
        for (size_t i = 0; i + 4 < control_points.size(); i += 4) {
            // 获取3次贝塞尔全部端点与控制点
            const auto &p0 = control_points[i];
            const auto &p1 = control_points[i + 1];
            const auto &p2 = control_points[i + 2];
            const auto &p3 = control_points[i + 3];
            // 创建采样t值的容器
            vector<double> t_values;
            // 默认第一个点为端点
            t_values.push_back(0.0);
            // 使用prev存储上一个尝试的采样点的坐标
            pair<double, double> prev = compute_coordinate_cubic_bezier(p0, p1, p2, p3, 0.0);
            // 用于存储累计的弧长，超过用户指定值后归零并装入t值
            double accumulated_length = 0.0;
            // 尝试的最小步长
            const double dt = 0.001;
            // 在1的范围内进行探测步长是否符合
            for (double t = dt; t <= 1.0; t += dt) {
                // 尝试的点
                auto p_t = compute_coordinate_cubic_bezier(p0, p1, p2, p3, t);
                // 累计弧长
                accumulated_length += distance_2d(prev, p_t);
                // 如果大于规定弧长
                if (accumulated_length >= pixel_step) {
                    // t值加入容器
                    t_values.push_back(t);
                    // 累计弧长清零
                    accumulated_length = 0.0;
                }
                // 存储当前尝试点为下一次的prev
                prev = p_t;
            }
            // 确保包括终点
            if (t_values.empty() || t_values.back() < 1.0)
                t_values.push_back(1.0);
            // 当前曲线的全部采样t值加入返回结果的容器
            all_t_values.push_back(t_values);
        }
        return all_t_values;
    }

    inline void print_t_for_sample(const vector<vector<double>>& t) {
        for (size_t i = 0; i < t.size(); i++) {
            cout << "t for cubic bezier group [" << i << "]: " << endl;
            for (size_t j = 0; j < t[i].size(); j++) {
                cout << t[i][j] << " ";
            }
            cout << endl;
            cout << "------------------------" << endl;
        }
    }
}


#endif //ROTO_2_CPP_UTILS_H
