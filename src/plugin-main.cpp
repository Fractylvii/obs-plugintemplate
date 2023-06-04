/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QWidget>
#include "HUD-dock.hpp"
#include "QioToggle.hpp"
#include "plugin-macros.generated.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

static void OBSEvent(enum obs_frontend_event event, void *hudWidget);

bool obs_module_load(void)
{
	//Gets reference to main OBS window, and passing that window into the class
	//This lets class know what it is a dockable widget to
	QWidget *main_window = (QWidget *)obs_frontend_get_main_window();
	HudWidget *hudWidget = new HudWidget(main_window);
	obs_frontend_push_ui_translation(obs_module_get_string);

	obs_frontend_add_dock(hudWidget);
	obs_frontend_add_event_callback(OBSEvent, hudWidget);

	blog(LOG_INFO, "plugin loaded successfully (version %s)",
	     PLUGIN_VERSION);
	return true;
}

void obs_module_unload()
{
	blog(LOG_INFO, "plugin unloaded");
}

void obs_module_post_load() 
{
	blog(LOG_INFO, "Post (version %s)",
	     PLUGIN_VERSION);
}

static void OBSEvent(enum obs_frontend_event event, void *hudWidget) {
	if (!hudWidget) {
		return;
	}
	HudWidget *hud = static_cast<HudWidget*>(hudWidget);

	switch (event) {
		case OBS_FRONTEND_EVENT_SCENE_CHANGED: //Turn off plugin if current scene =/= scene which was current when hud enabled
			break;
		case OBS_FRONTEND_EVENT_SCENE_LIST_CHANGED: //update scenes available for choice
			hud->loadScenes();
			hud->releaseScenes();
			break;
		case OBS_FRONTEND_EVENT_SCENE_COLLECTION_CHANGED: //update scenes available for choice
			hud->loadScenes();
			hud->releaseScenes();
			break;
		case OBS_FRONTEND_EVENT_FINISHED_LOADING: //Load necessary scenes/data to plugin
			hud->loadScenes();
			hud->releaseScenes();
			break;
		case OBS_FRONTEND_EVENT_EXIT: //Implement force plugin disable
			break;
		default:
			break;
	}

}