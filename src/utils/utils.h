//
// Created by 12544 on 25-5-20.
//

#ifndef ROTO_2_CPP_UTILS_H
#define ROTO_2_CPP_UTILS_H

#include "../macros.h"
#include "../data/CurveUtils.h"

namespace roto_util {
    // -------------------------------------
    // 贝塞尔工具函数部分
    // -------------------------------------

    // 三次贝塞尔线性插值
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

    //计算给定t值的三次贝塞尔曲线的坐标
    inline pair<double, double> compute_coordinate_cubic_bezier(const pair<double, double> &p0, const pair<double, double> &p1, const pair<double, double> &p2, const pair<double, double> &p3,
                                                                const double t) {
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

    // 二维点的几何距离
    inline double distance_2d(const pair<double, double> &a, const pair<double, double> &b) {
        const double dx = a.first - b.first;
        const double dy = a.second - b.second;
        // 两点距离
        return sqrt(dx * dx + dy * dy);
    }

    // 等弧长采样三次贝塞尔，返回t值
    inline vector<vector<double> > sample_cubic_bezier_by_pixel_length(const vector<pair<double, double> > &control_points, const double pixel_step = 1.0) {
        vector<vector<double> > all_t_values;
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
            constexpr double dt = 0.001;
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

    // 打印采样的t值
    inline void print_t_for_sample(const vector<vector<double> > &t) {
        for (size_t i = 0; i < t.size(); i++) {
            cout << "t for cubic bezier group [" << i << "]: " << endl;
            for (size_t j = 0; j < t[i].size(); j++) {
                cout << t[i][j] << " ";
            }
            cout << endl;
            cout << "------------------------" << endl;
        }
    }

    // pair和vector复合类型的点容器转换为传统数组，使用智能指针管理
    inline unique_ptr<double[]> control_points_to_pointer(const array<BezierCurve, g_frame_num> &curves, const int n_curve, const int idx1, const int idx2) {
        const auto n_point_xy = n_curve * 4 * 2; // 点的坐标分量个数 = 曲线个数 * 4（3次贝塞尔） * 2（2维坐标）
        const auto n_frame = idx2 - idx1 + 1; // 包含开始和结尾
        auto buffer = make_unique<double[]>(n_point_xy * n_frame);

        for (auto i_frame = idx1; i_frame < idx2 + 1; i_frame++) {
            const auto &points = curves[i_frame].getControlPoints();
            for (auto i_pair = 0; i_pair < n_point_xy / 2; i_pair++) {
                auto [x, y] = points[i_pair];

                buffer[i_frame * n_point_xy + i_pair * 2 + 0] = x;
                buffer[i_frame * n_point_xy + i_pair * 2 + 1] = y;
            }
        }

        return move(buffer);
    }

    // -------------------------------------
    // 残差计算与优化部分
    // -------------------------------------

    // 坐标估算 为ceres设计
    template<typename T>
    void evaluate_bezier_curve_ceres(const T *p0, const T *p1, const T *p2, const T *p3,
                                     T t, T *result) {
        T u = T(1.0) - t;
        T b0 = u * u * u;
        T b1 = T(3.0) * u * u * t;
        T b2 = T(3.0) * u * t * t;
        T b3 = t * t * t;

        result[0] = b0 * p0[0] + b1 * p1[0] + b2 * p2[0] + b3 * p3[0];
        result[1] = b0 * p0[1] + b1 * p1[1] + b2 * p2[1] + b3 * p3[1];
    }

    // 从容器中获取需要的控制点的信息 为ceres设计
    template<typename T>
    void extract_control_point_ceres(const T *ctrl_points_xy, const int i_frame, const int n_curve, const int i_curve, const int i_point, T *result) {
        int idx_x = i_frame * (n_curve * 4 * 2) + i_curve * (4 * 2) + i_point * 2 + 0;
        int idx_y = i_frame * (n_curve * 4 * 2) + i_curve * (4 * 2) + i_point * 2 + 1;
        result[0] = ctrl_points_xy[idx_x];
        result[1] = ctrl_points_xy[idx_y];
    }

    // 计算两点距离的平方 为ceres设计
    template<typename T>
    T squared_distance_ceres(const T* a, const T* b) {
        return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
    }


    // 长度项
    struct ELResidual {
        template<typename T>
        bool operator()(const T *ctrl_points_xy, T *residual) const {
            // 1次根据2个帧的信息计算
            for (auto i_frame = 0; i_frame < n_frame - 1; i_frame++) {
                for (auto i_curve = 0; i_curve < n_curve; i_curve++) {
                    auto n_sample = t_values[i_curve].size();
                    // 1次根据2个采样点计算
                    for (auto i_sample = 0; i_sample < n_sample - 1; i_sample++) {
                        // -----------
                        // 命名规则：ci_j - i:帧的序号 - j:控制点的序号
                        // -----------
                        double c0_0[2], c0_1[2], c0_2[2], c0_3[2]; // 当前帧的4个控制点
                        double c1_0[2], c1_1[2], c1_2[2], c1_3[2]; // 下一帧的4个控制点
                        // 获取控制点坐标
                        extract_control_point_ceres(ctrl_points_xy, i_frame, n_curve, i_curve, 0, c0_0);
                        extract_control_point_ceres(ctrl_points_xy, i_frame, n_curve, i_curve, 1, c0_1);
                        extract_control_point_ceres(ctrl_points_xy, i_frame, n_curve, i_curve, 2, c0_2);
                        extract_control_point_ceres(ctrl_points_xy, i_frame, n_curve, i_curve, 3, c0_3);
                        extract_control_point_ceres(ctrl_points_xy, i_frame + 1, n_curve, i_curve, 0, c1_0);
                        extract_control_point_ceres(ctrl_points_xy, i_frame + 1, n_curve, i_curve, 1, c1_1);
                        extract_control_point_ceres(ctrl_points_xy, i_frame + 1, n_curve, i_curve, 2, c1_2);
                        extract_control_point_ceres(ctrl_points_xy, i_frame + 1, n_curve, i_curve, 3, c1_3);
                        // -----------
                        // 命名规则：ti - i:采样位置的序号
                        // -----------
                        const double t0 = t_values[i_curve][i_sample]; // 第1个对应位的t
                        const double t1 = t_values[i_curve][i_sample + 1]; // 第2个对应位的t
                        // -----------
                        // 命名规则：si_j - i:帧的序号 - j:采样点的序号
                        // -----------
                        double s0_0[2], s0_1[2], s1_0[2], s1_1[2]; // 4个采样点
                        // 获取采样点坐标
                        evaluate_bezier_curve_ceres(c0_0, c0_1, c0_2, c0_3, t0, s0_0);
                        evaluate_bezier_curve_ceres(c0_0, c0_1, c0_2, c0_3, t1, s0_1);
                        evaluate_bezier_curve_ceres(c1_0, c1_1, c1_2, c1_3, t0, s1_0);
                        evaluate_bezier_curve_ceres(c1_0, c1_1, c1_2, c1_3, t1, s1_1);
                        // 计算边长的平方差
                        T len_sq_0 = squared_distance_ceres(s0_0, s0_1);
                        T len_sq_1 = squared_distance_ceres(s1_0, s1_1);
                        T diff = len_sq_0 - len_sq_1;
                        // 加入残差
                        residual[0] = g_w_l * diff * diff;
                    }
                }
            }
            return true;
        }

        int n_curve;
        int n_frame;
        vector<vector<double>> &t_values;
    };

    // 曲率变化项
    struct ECResidual {};

    // 速度项
    struct EVResidual {};

    // 图像项
    struct EIResidual {};

    // 边缘项
    struct EGResidual {};
}


#endif //ROTO_2_CPP_UTILS_H
