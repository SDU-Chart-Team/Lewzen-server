#include "double_arrow.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void DoubleArrow::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("double_arrow");

        // 维护图形SVG
        SVGIG->children({});                // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        Control0 = createCorePoint("Control0", getX() + getWidth() * 0.25, getY() + getHeight() * 0.35);
        Control0->setColor("orange");
        Control0->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                            {
                                if (!corePointMoving)
                                    return;
                                if (nx < (getX()))
                                {
                                    Control0->setX(getX());
                                }
                                if (nx > getX() + getWidth() * 0.5)
                                {
                                    Control0->setX(getX() + getWidth() * 0.5);
                                }
                                if (ny < getY())
                                {
                                    Control0->setY(getY());
                                }
                                if (ny > getY() + getHeight() * 0.5)
                                {
                                    Control0->setY(getY() + getHeight() * 0.5);
                                }
                            });
        corePoints[Control0->getId()] = Control0;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&DoubleArrow::getPath, this);
        SVGIPath->D.bind(_getPath);
    } // 拷贝
    ComponentAbstract &DoubleArrow::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const DoubleArrow &>(comp);
        // 拷贝关键点位置
        *Control0 = *(p.Control0);
        return *this;
    }
    // 序列化，并记录已操作的
    void DoubleArrow::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &DoubleArrow::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);
        SVGIG->add(SVGIPath);
        // 注册关键点
        Control0 = corePoints["Control0"];

        
        return *this;
    }
    //// Basics虚接口
    void DoubleArrow::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        double disY0 = Control0->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX0 = Control0->getX() - getX();
        if (id == "Control0")
        {                           // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control0 += createPoint(dx, 0);
            *Control0 += createPoint(0, dy);
            corePointMoving = false;
        }
        else
        {
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX() +disX0 > getX() + getWidth() * 0.5)
                disX0 =  getWidth() * 0.5;
            if ( getY() +disY0 > getY() + getHeight() * 0.5)
                disY0 = getHeight() * 0.5;
            *Control0 = createPoint(getX() + disX0, getY() + disY0); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    ////DoubleArrow interface
    const std::string DoubleArrow::getPath() const
    {
        auto p0 = createPoint(getX(), getY() + getHeight() * 0.5);
        auto p1 = createPoint(Control0->getX(), getY());
        auto p2 = createPoint(Control0->getX(), Control0->getY());
        auto p3 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), Control0->getY());
        auto p4 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), getY());
        auto p5 = createPoint(getX() + getWidth(), getY() + getHeight() * 0.5);
        auto p6 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), getY() + getHeight());
        auto p7 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), getY() + getHeight() - (Control0->getY() - getY()));
        auto p8 = createPoint(Control0->getX(), getY() + getHeight() - (Control0->getY() - getY()));
        auto p9 = createPoint(Control0->getX(), getY() + getHeight());
        auto p10 = createPoint(getX(), getY() + getHeight() * 0.5);
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        ss << "L " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "L " << p8.get_x() << " " << p8.get_y() << " ";
        ss << "L " << p9.get_x() << " " << p9.get_y() << " ";
        ss << "L " << p10.get_x() << " " << p10.get_y() << " ";
        return ss.str();
    }
}