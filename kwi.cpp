#include <wayfire/plugin.hpp>
#include <wayfire/view.hpp>
#include <wayfire/core.hpp>
#include <wayfire/workspace-manager.hpp>
#include <wayfire/signal-definitions.hpp>

class primary_monitor_switch_t : public wf::plugin_interface_t
{
	std::unique_ptr<wf::workspace_manager::anchored_area> anchored_area_top;
	std::unique_ptr<wf::workspace_manager::anchored_area> anchored_area_left;
	
	wf::signal_connection_t created_cb = [=] (wf::signal_data_t *data){
			//test
			auto view = get_signaled_view(data);
			
			if (view->get_app_id() == "eu.kosy.Jupiter"){				
				int width = output->get_layout_geometry().width;
				int height = output->get_layout_geometry().width;
				
				if(view->get_title() == "panelWindow"){
					LOGI("Found 1");
					view->move(0, 0);
					view->set_decoration(NULL);
					view->resize(width, 30);
					output->workspace->add_view(view, wf::LAYER_TOP);
					
					anchored_area_top = std::make_unique<wf::workspace_manager::anchored_area>();
					anchored_area_top->reflowed = 0;
					output->workspace->add_reserved_area(anchored_area_top.get());
					anchored_area_top->edge = wf::workspace_manager::ANCHORED_EDGE_TOP;
					anchored_area_top->reserved_size = 30;
					anchored_area_top->real_size = 300;
					
					output->workspace->reflow_reserved_areas();
					view->move(0, 0);
				}
				
				if(view->get_title() == "dockWindow"){
					LOGI("Found 2");
					view->move(0, 30);
					view->set_decoration(NULL);
					view->resize(80, height);
					output->workspace->add_view(view, wf::LAYER_TOP);
					
					anchored_area_left = std::make_unique<wf::workspace_manager::anchored_area>();
					anchored_area_left->reflowed = 0;
					output->workspace->add_reserved_area(anchored_area_left.get());
					anchored_area_left->edge = wf::workspace_manager::ANCHORED_EDGE_LEFT;
					anchored_area_left->reserved_size = 80;
					anchored_area_left->real_size = 300;
					
					output->workspace->reflow_reserved_areas();
					view->move(0, 30);
				}
			}
	};
	
	wf::signal_connection_t closed_cb = [=] (wf::signal_data_t *data){
			//test
			auto view = get_signaled_view(data);
			
			if (view->get_app_id() == "eu.kosy.Jupiter"){
				
				if(anchored_area_top){
					output->workspace->remove_reserved_area(anchored_area_top.get());
					anchored_area_top = nullptr;
				}
				
				if(anchored_area_left){
					output->workspace->remove_reserved_area(anchored_area_left.get());
					anchored_area_left = nullptr;
				}
				
				output->workspace->reflow_reserved_areas();
			}
	};
	
  public:
    void init() override
    {
        LOGI("Init Test");
        output->connect_signal("view-mapped", &created_cb);
        output->connect_signal("view-unmapped", &closed_cb);
    }

    void fini() override
    {
        /* Destroy plugin */
    }
};

DECLARE_WAYFIRE_PLUGIN(kosy-wayfire-integration)
