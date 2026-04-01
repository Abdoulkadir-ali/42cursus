#include "functions/gui/render.h"
#include "functions/gui/editor.h"
#include "functions/gui/map.h"
#include <pthread.h>

void poll_map_job(t_gui *gui)
{
	t_map_job *job;

	job = &gui->map_job;
	if (!job->active || !job->done)
		return ;
	pthread_join(job->tid, NULL);
	job->active = false;
	if (!job->entry || !job->entry->scene)
		return ;
	gui->map_info.current = job->entry;
	gui->scene = job->entry->scene;
	scene_snap_take(&job->entry->snap, gui);
	gui->cam_ctrl.camera = &gui->scene->camera;
	reset_camera_view(gui);
	clear_selection(gui);
	gui->render.dirty = true;
}
