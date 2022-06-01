#ifndef __LEWZENSERVER_NOTES__
#define __LEWZENSERVER_NOTES__

#include "../comp/rectangle.h"

namespace LewzenServer {
    class Notes : virtual public Rectangle {
    protected:
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;
        double padding = 20;
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

        //// Basics virtual interface
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// IsometricCube interface
        // 计算路径
        const std::string getPath() const;
    };
}
#endif