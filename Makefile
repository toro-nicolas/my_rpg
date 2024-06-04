##
## EPITECH PROJECT, 2023
## my_printf
## File description:
## The main Makefile of our project
##

COLORS = $$(seq 1 7 | shuf -n 1)
RED = $$(tput setaf $(COLORS))
GREEN = $$(tput setaf $(COLORS))
YELLOW = $$(tput setaf $(COLORS))
RESET = $$(tput sgr0)
MAKEFLAGS += --no-print-directory

CFLAGS = -I./include -Wextra
CFLAGS += -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm
LFLAGS = -L./lib -lmy -llist -lm
TEST_FLAGS = --coverage -lcriterion -lgcov

SRC	=	src/main.c

SRC += src/create/create_button.c
SRC += src/create/create_entity.c
SRC += src/create/create_rect.c
SRC += src/create/create_sprite.c
SRC += src/create/create_text.c

SRC += src/display/intro/display_intro.c
SRC += src/display/intro/init_sage.c
SRC += src/display/intro/init_bg.c
SRC += src/display/intro/get_ptr_intro.c
SRC += src/display/intro/display_talk.c
SRC += src/display/intro/display_bonus.c

SRC += src/display/display_main.c
SRC += src/display/display_menu.c
SRC += src/display/display_pause.c
SRC += src/display/display_settings.c
SRC += src/display/display_bind.c
SRC += src/display/display_npc.c
SRC += src/display/display_equipments.c
SRC += src/display/display_globalstat.c

SRC += src/display/entities/display_entities.c
SRC += src/display/entities/display_stat.c

SRC += src/display/player/display_player.c
SRC += src/display/player/display_levelbar.c
SRC += src/display/player/display_statup.c
SRC += src/display/player/display_player_stat.c
SRC += src/display/player/display_item.c

SRC += src/display/hud/display_hud.c

SRC += src/update/update_player.c
SRC += src/update/update_player2.c
SRC += src/update/update_item.c
SRC += src/update/update_menu.c
SRC += src/update/update_main.c
SRC += src/update/update_pause.c
SRC += src/update/update_settings.c
SRC += src/update/update_bind.c
SRC += src/update/update_intro.c
SRC += src/update/update_hud.c
SRC += src/update/update_entities.c

SRC += src/action/player/action_player.c
SRC += src/action/player/atk_up.c
SRC += src/action/player/def_up.c
SRC += src/action/player/hp_up.c
SRC += src/action/player/attack_mob.c

SRC += src/action/object/interact.c

SRC += src/action/npc/troll.c
SRC += src/action/npc/speak.c
SRC += src/action/npc/die_loser.c
SRC += src/action/npc/quest.c
SRC += src/action/npc/drop_itemnpc.c
SRC += src/action/npc/mob_npc.c
SRC += src/action/npc/inventory_npc.c
SRC += src/action/npc/end.c

SRC += src/entities/gladiator.c
SRC += src/entities/hitbox.c
SRC += src/entities/map_case.c
SRC += src/entities/mob_collisions.c
SRC += src/entities/mimics.c
SRC += src/entities/mob_action.c
SRC += src/entities/mob_animation.c
SRC += src/entities/monsters.c
SRC += src/entities/vectors.c
SRC += src/entities/path_finding.c
SRC += src/entities/random_npc.c

SRC += src/events/events_intro.c
SRC += src/events/events_main.c
SRC += src/events/events_menu.c
SRC += src/events/events_player.c
SRC += src/events/events_pause.c
SRC += src/events/events_settings.c
SRC += src/events/events_bind.c

SRC += src/button_function/event_button.c
SRC += src/button_function/display_button.c
SRC += src/button_function/menu.c
SRC += src/button_function/pause.c
SRC += src/button_function/settings.c
SRC += src/button_function/bind.c
SRC += src/button_function/bind2.c
SRC += src/button_function/bind3.c

SRC += src/save/save.c
SRC += src/save/save_entities.c
SRC += src/save/save_map.c
SRC += src/save/save_player.c
SRC += src/save/load.c
SRC += src/save/load_entities.c
SRC += src/save/load_map.c
SRC += src/save/load_player.c
SRC += src/save/check_file.c

SRC += src/music/play.c
SRC += src/music/volume.c

SRC += src/thread.c
SRC += src/analyse_events.c
SRC += src/init_game.c
SRC += src/get_ptr.c
SRC += src/get_ptr_2.c
SRC += src/get_player_infos.c

SRC += src/game_loop.c
SRC += src/create/create_map/create_map.c
SRC += src/create/create_map/generate_map.c

OBJ	=	$(SRC:.c=.o)

NAME = my_rpg

all: libmy liblist compile
	@echo "$(RESET)"

libmy:
	@echo "$(RED)------------------"
	@echo "$(RED)doing libmy"
	@make -s -C ./lib/my/
	@echo "$(RED)------------------"

liblist:
	@echo "$(RED)------------------"
	@echo "$(GREEN)doing liblist"
	@make -s -C ./lib/list/
	@echo "$(RED)------------------"

compile: $(OBJ)
	@gcc $(SRC) -o $(NAME) $(CFLAGS) $(LFLAGS)

valgrind:
	@gcc $(SRC) -g3 $(CFLAGS) $(LFLAGS)
	@valgrind -s ./$(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

clean_lib:
	@make fclean -C./lib/my/
	@make fclean -C./lib/list/
	@make fclean -C./tests/

re:	clean_lib fclean all

unit_tests: re
	make unit_tests -C ./tests/

tests_run: re
	make -C ./tests/
	@gcovr


# Documentation
doc: tests_run
	@doxygen Doxyfile
	@gcovr \
    --exclude lib/my/my_printf/round_flag_a.c \
    --exclude lib/mylist/my_list_to_array.c \
    --exclude lib/mylist/my_show_list.c \
	--branch --html-details docs/tests/test.html
	@echo -e "\033[1;33mDocumentation generated.\033[0m"
	@google-chrome docs/html/index.html
	@google-chrome docs/tests/test.html
