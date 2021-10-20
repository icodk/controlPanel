idf_component_register(SRCS main.c 
							frmProcess.c 
							frmInfo.c
							frmNetwork.c
							dataStorage.c 
							ui_common.c 
							counter_conf.c 
							process.c 
							text_table.c
							menu.c
							menuStruct.c
							ethernet_cfg.c
							wifi_cfg.c
							tempSensor.c
							frmOvenControl.c
							
							)

##execute_process(COMMAND cmd /C git describe --abbrev=7 --dirty --always --tags > gitversion1.c )
idf_build_set_property(COMPILE_DEFINITIONS "-DSTR_GIT_VERSION=\"${PROJECT_VER}\"" APPEND)

