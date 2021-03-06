#include "weak_relation.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void WeakRelation::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("weak_relation");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&WeakRelation::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &WeakRelation::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);


        auto &p = dynamic_cast<const WeakRelation &>(comp); 
        return *this;
    }
    // 序列化，并记录已操作的
    void WeakRelation::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &WeakRelation::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        return *this;
    }
    //// Basics虚接口
    void WeakRelation::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////WeakRelation interface
    const std::string WeakRelation::getPath() const {
        auto p0 = createPoint(getX()+getWidth()*0.5, getY());
        auto p1 = createPoint(getX()+getWidth(), getY()+getHeight()*0.5);
        auto p2 = createPoint(getX()+getWidth()*0.5, getY()+getHeight());
        auto p3 = createPoint(getX(), getY()+getHeight()*0.5);
        auto p4 = createPoint(getX()+getWidth()*0.5, getY());
        auto p5 = createPoint(getX()+getWidth()*0.5, getY()+getHeight()*0.1);
        auto p6 = createPoint(getX()+getWidth()*0.9, getY()+getHeight()*0.5);
        auto p7 = createPoint(getX()+getWidth()*0.5, getY()+getHeight()*0.9);
        auto p8 = createPoint(getX()+getWidth()*0.1, getY()+getHeight()*0.5);
        auto p9 = createPoint(getX()+getWidth()*0.5, getY()+getHeight()*0.1);
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "M " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        ss << "L " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "L " << p8.get_x() << " " << p8.get_y() << " ";
        ss << "L " << p9.get_x() << " " << p9.get_y() << " ";
        return ss.str();

    }
}