run_app:
	@echo -e "Running '$(APP_NAME)' on '$(HERO_TARGET_HOST):$(HERO_TARGET_PATH_APPS)/$(APP_NAME)'"
	@ssh -t $(HERO_TARGET_HOST) 'cd ${HERO_TARGET_PATH_APPS}; ./$(APP_NAME) $(RUN_ARGS)'

deploy_app: clean_board
	@echo -e "Deploying '$(APP_NAME)' to '$(HERO_TARGET_HOST):$(HERO_TARGET_PATH_APPS)/$(APP_NAME)'"
	@scp $(BUILD_DIR)/$(APP_NAME) $(HERO_TARGET_HOST):$(HERO_TARGET_PATH_APPS)

clean_board:
	@echo -e "Cleaning '$(HERO_TARGET_HOST):$(HERO_TARGET_PATH_APPS)/$(APP_NAME)'"
	@ssh $(HERO_TARGET_HOST) "rm -f $(HERO_TARGET_PATH_APPS)/$(APP_NAME)"