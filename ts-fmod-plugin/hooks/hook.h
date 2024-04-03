#pragma once

namespace hooks
{
    class hook
    {
    protected:
        bool installed_ = false;

    public:
        virtual ~hook() = default;
        virtual bool install();

        virtual void uninstall();
    };
}
