#include "mon_manager/mon_manager.h"
#include <timer_session/connection.h>
#include <base/env.h>
#include <base/printf.h>
#include <base/process.h>
#include <util/xml_node.h>
#include <util/xml_generator.h>
#include <string>
#include <util/string.h>
#include <trace_session/connection.h>
#include <os/config.h>
namespace Mon_manager{
	
	Mon_manager::Mon_manager() {}

	void Mon_manager::update_info(Genode::Dataspace_capability ds_cap)
	{
		num_threads=100;
		Monitoring_object *threads = Genode::env()->rm_session()->attach(ds_cap);
		static Timer::Connection timer;
		static Genode::Trace::Connection trace(1024*4096, 64*4096, 0);
		Genode::Trace::Subject_id subjects[num_threads];
		size_t num_subjects = trace.subjects(subjects, num_threads);
		Genode::Trace::RAM_info init;
		for (size_t i = 0; i < num_subjects; i++) {
			Genode::Trace::CPU_info cpu_info = trace.cpu_info(subjects[i]);
			Genode::Trace::RAM_info ram_info = trace.ram_info(subjects[i]);
			if(Genode::strcmp(ram_info.session_label().string(), "init")!=0) {
       				threads[i].session_label=ram_info.session_label();
				threads[i].thread_name=ram_info.thread_name();
				threads[i].prio=cpu_info.prio();
				threads[i].execution_time=cpu_info.execution_time();
				threads[i].id=cpu_info.id();
				threads[i].foc_id=cpu_info.foc_id();
				threads[i].ram_used=ram_info.ram_used();
				threads[i].ram_quota=ram_info.ram_quota();
				threads[i].pos_rq=cpu_info.pos_rq();
			}else {
				init=ram_info;
			}
						
		}
		Genode::Trace::SCHEDULER_info scheduler_info = trace.scheduler_info(subjects[0]);
		ram_avail=init.ram_quota();
		idle0=scheduler_info.idle0();
		idle1=scheduler_info.idle1();
		idle2=scheduler_info.idle2();
		idle3=scheduler_info.idle3();	
		core0_is_online=scheduler_info.core0_is_online();
		core1_is_online=scheduler_info.core1_is_online();
		core2_is_online=scheduler_info.core2_is_online();
		core3_is_online=scheduler_info.core3_is_online();
		num_cores=scheduler_info.num_cores();
	}

	Genode::Dataspace_capability Mon_manager::init_ds_cap(int num_threads) {
		if(num_threads<=100) {
			Genode::Dataspace_capability mon_ds_cap = Genode::env()->ram_session()->alloc(num_threads*sizeof(Monitoring_object));
			Genode::env()->rm_session()->attach(mon_ds_cap);
			return mon_ds_cap;
		} else {
			PDBG("Don't mess with me!");
			return Genode::env()->ram_session()->alloc(0);
		}
	}

	int Mon_manager::get_num_cores() {
		return num_cores;
	}
	
	Genode::Trace::Execution_time Mon_manager::get_idle_time(int core) {
		if(core==0) return idle0;
		if(core==1) return idle1;
		if(core==2) return idle2;
		if(core==3) return idle3;
	}

	bool Mon_manager::is_core_online(int core) {
		if(core==0) return core0_is_online;
		if(core==1) return core1_is_online;
		if(core==2) return core2_is_online;
		if(core==3) return core3_is_online;
	}
}
