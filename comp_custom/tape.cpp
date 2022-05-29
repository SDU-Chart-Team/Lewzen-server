#include "tape.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Tape::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("tape");

        // 维护图形SVG
        SVGIG->children({});                // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        Control = createCorePoint("Control", getX() + getWidth() * 0.5, getY() + getHeight() * 0.25);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                           {
                               if (!corePointMoving)
                                   return;
                               if (ny < getY())
                                   Control->setY(getY()); // 不允许超过高度的一半
                               if (ny > getY() + getHeight() * 0.5)
                                   Control->setY(getY() + getHeight() * 0.5); // 不允许低于矩形的Y坐标
                           });
        corePoints[Control->getId()] = Control;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Tape::getPath, this);
        SVGIPath->D.bind(_getPath);
    } // 拷贝
    ComponentAbstract &Tape::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Tape &>(comp);
        // 拷贝关键点位置
        *Control = *(p.Control);
        return *this;
    }
    // 序列化，并记录已操作的
    void Tape::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Tape::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        Control = corePoints["Control"];
        return *this;
    }
    //// Basics虚接口
    void Tape::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        double disY = Control->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX = Control->getX() - getX();
        double ptgX = ((Control->getX() - getX()) / getWidth()) * getWidth();
        double ptgY = ((Control->getY() - getY()) / getHeight()) * getHeight();
        if (id == "Control")
        {                           // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(0, dy);
            corePointMoving = false;
        }
        else
        { // 移动其他点
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX() + ptgX > getX() + getWidth())
                ptgX = getWidth();
            if (getY() + ptgY > getY() + getHeight() * 0.5)
                ptgY = getHeight() * 0.5;
            *Control = createPoint(getX() + ptgX, getY() + ptgY); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    ////Tape interface
    const std::string Tape::getPath() const
    {
        auto p0 = createPoint(getX(), Control->getY());
        auto p1 = createPoint(getX() + getWidth() * 0.25, getY() + (Control->getY() - getY()) * 2);
        auto p2 = createPoint(getX() + getWidth() * 0.5, Control->getY());
        auto p3 = createPoint(getX() + getWidth() * 0.75, getY());
        auto p4 = createPoint(getX() + getWidth(), Control->getY());
        auto p5 = createPoint(getX() + getWidth(), getY() + getHeight() - (Control->getY() - getY()));
        auto p6 = createPoint(getX() + getWidth() * 0.75, getY() + getHeight() - (Control->getY() - getY()) * 2);
        auto p7 = createPoint(getX() + getWidth() * 0.5, getY() + getHeight() - (Control->getY() - getY()));
        auto p8 = createPoint(getX() + getWidth() * 0.25, getY() + getHeight());
        auto p9 = createPoint(getX(), getY() + getHeight() - (Control->getY() - getY()));
        auto p10 = createPoint(getX(), Control->getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "Q " << p1.get_x() << " " << p1.get_y() << " " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "Q " << p3.get_x() << " " << p3.get_y() << " " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "Q " << p6.get_x() << " " << p6.get_y() << " " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "Q " << p8.get_x() << " " << p8.get_y() << " " << p9.get_x() << " " << p9.get_y() << " ";
        ss << "L " << p10.get_x() << " " << p10.get_y() << " ";
        return ss.str();
    }
}