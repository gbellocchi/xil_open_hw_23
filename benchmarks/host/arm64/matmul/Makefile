ROOT := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

############################ Sources ############################

APP_NAME := mmult_sw

-include ${APP_UTILS_DIR}/app.mk
-include ${BOARD_UTILS_DIR}/board.mk

all: build_env build_app clean_board deploy_app
clean: clean_local