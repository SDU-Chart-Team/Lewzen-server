#ifndef __LEWZENSERVER_AND__
#define __LEWZENSERVER_AND__

#include "../comp_module/comp_rotatable.h"

namespace LewzenServer
{
    class And : virtual public ComponentRotatable
    {
    protected:
        // SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;
        // 关键点别名
        std::shared_ptr<CorePoint> LT, L, LB, B, RB, R, RT, T;
        //
        bool corePointMoving = false;

    public:
        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// 图形接口

        /**
         * @brief 
         * 
         * 
         * 
         * @return std::string "M LT.X LT.Y Q RT.X RT.Y R.X R.Y Q RB.X RB.Y LB.X LB.Y Q T.X R.Y LT.X LT.Y"
         */
        virtual std::string getD() const;
    };
}

#endif