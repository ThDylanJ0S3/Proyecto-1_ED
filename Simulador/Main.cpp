#include "Funciones.h"

void main ( )
{
	if ( !al_init ( ) ) {
		al_show_native_message_box ( NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL );
		return;
	}

	al_init_font_addon ( );
	al_init_ttf_addon ( );
	al_init_image_addon ( );
	al_init_primitives_addon ( );
	al_install_keyboard ( );
	al_install_mouse ( );

	int ResX = 800;
	int ResY = 500;
	int mousex = 0;
	int mousey = 0;
	int ocupacion = 0;
	int espacios = 0;


	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info ( 0, &monitor );
	const int RX = monitor.x2 - monitor.x1;
	const int RY = monitor.y2 - monitor.y1;

	ALLEGRO_DISPLAY * pantalla = al_create_display ( ResX, ResY );
	al_set_window_position ( pantalla, RX / 4 - ResX / 4, RY / 4 - ResY / 4 );
	al_set_window_title ( pantalla, "Simulador Estacionador Automático" );

	if ( !pantalla )
	{
		al_show_native_message_box ( NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR );
		return;
	}

	ALLEGRO_EVENT_QUEUE * cola_eventos = al_create_event_queue ( );

	ALLEGRO_TIMER * timer = al_create_timer ( 1.0 / FPS );

	ALLEGRO_FONT * Fuente = al_load_font ( "pixel.ttf", 40, NULL );
	ALLEGRO_FONT * Fuente2 = al_load_font ( "pixel.ttf", 20, NULL );


	al_register_event_source ( cola_eventos, al_get_timer_event_source ( timer ) );
	al_register_event_source ( cola_eventos, al_get_display_event_source ( pantalla ) );
	al_register_event_source ( cola_eventos, al_get_keyboard_event_source ( ) );
	al_register_event_source ( cola_eventos, al_get_mouse_event_source ( ) );

	bool hecho = true;
	bool instr = true;
	bool submenu = true;

	al_start_timer ( timer );

	while ( hecho ) {
		ALLEGRO_EVENT eventos;
		al_wait_for_event ( cola_eventos, &eventos );
		if ( eventos.type == ALLEGRO_EVENT_MOUSE_AXES )
		{
			mousex = eventos.mouse.x;
			mousey = eventos.mouse.y;

		}
		if ( eventos.type == ALLEGRO_EVENT_TIMER )
		{
			if ( eventos.timer.source == timer )
			{
				al_clear_to_color ( al_map_rgb ( 0, 0, 0 ) );
				al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 2, 100, ALLEGRO_ALIGN_CENTRE, "Simulador de estacionador" );
				al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 200, ALLEGRO_ALIGN_CENTRE, "Iniciar" );
				al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 250, ALLEGRO_ALIGN_CENTRE, "Instrucciones" );
				al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 350, ALLEGRO_ALIGN_CENTRE, "Salir" );
			}
		}
		if ( ( mousex >= ResX / 2 - 30 && mousex <= ResX / 2 + 30 ) && ( mousey >= 210 ) && ( mousey <= 230 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 2, 200, ALLEGRO_ALIGN_CENTRE, "Iniciar" );
			if ( eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( eventos.mouse.button & 1 ) {
					while ( submenu ) {
						ALLEGRO_EVENT eventossub;
						al_wait_for_event ( cola_eventos, &eventossub );
						if ( eventossub.type == ALLEGRO_EVENT_MOUSE_AXES )
						{
							mousex = eventossub.mouse.x;
							mousey = eventossub.mouse.y;

						}
						if ( eventossub.type == ALLEGRO_EVENT_TIMER )
						{
							if ( eventossub.timer.source == timer )
							{
								al_clear_to_color ( al_map_rgb ( 0, 0, 0 ) );
								al_draw_text ( Fuente, al_map_rgb ( 250, 220, 250 ), ResX / 2, 70, ALLEGRO_ALIGN_CENTRE, "Una planta de un piso." );
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 120, ALLEGRO_ALIGN_CENTRE, "Una planta de dos pisos." );
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 170, ALLEGRO_ALIGN_CENTRE, "Una torre con dos espacios por piso." );
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 220, ALLEGRO_ALIGN_CENTRE, "Una torre con un pasillo horizontal." );
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 4, 330, ALLEGRO_ALIGN_CENTRE, "Regresar" );
							}
						}
						if ( ( mousex >= ResX / 2 - 140 && mousex <= ResX / 2 + 140 ) && ( mousey >= 70 ) && ( mousey <= 100 ) ) {
							al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 2, 70, ALLEGRO_ALIGN_CENTRE, "Una planta de un piso." );
							{
								if ( eventossub.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
								{
									if ( eventossub.mouse.button & 1 ) {
										submenu = false;
										recibir_parametros ( ocupacion, espacios );
										al_set_target_backbuffer ( pantalla );
										juego_una_planta_un_piso(ocupacion,espacios);
										break;
									}
								}
							}
						}
						if ( ( mousex >= ResX / 2 - 160 && mousex <= ResX / 2 + 160 ) && ( mousey >= 120 ) && ( mousey <= 150 ) ) {
							al_draw_text ( Fuente, al_map_rgb ( 250, 250, 110 ), ResX / 2, 120, ALLEGRO_ALIGN_CENTRE, "Una planta de dos pisos." );
							{
								if ( eventossub.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
								{
									if ( eventossub.mouse.button & 1 ) {
										submenu = false;
										//juego();------------------------------------------
										break;
									}
								}
							}
						}
						if ( ( mousex >= ResX / 2 - 230 && mousex <= ResX / 2 + 230 ) && ( mousey >= 170 ) && ( mousey <= 200 ) ) {
							al_draw_text ( Fuente, al_map_rgb ( 250, 250, 110 ), ResX / 2, 170, ALLEGRO_ALIGN_CENTRE, "Una torre con dos espacios por piso." );
							{
								if ( eventossub.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
								{
									if ( eventossub.mouse.button & 1 ) {
										submenu = false;
										//juego();------------------------------------------
										break;
									}
								}
							}
						}
						if ( ( mousex >= ResX / 2 - 240 && mousex <= ResX / 2 + 240 ) && ( mousey >= 220 ) && ( mousey <= 250 ) ) {
							al_draw_text ( Fuente, al_map_rgb ( 250, 250, 110 ), ResX / 2, 220, ALLEGRO_ALIGN_CENTRE, "Una torre con un pasillo horizontal." );
							{
								if ( eventossub.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
								{
									if ( eventossub.mouse.button & 1 ) {
										submenu = false;
										//juego();------------------------------------------
										break;
									}
								}
							}
						}
						if ( ( mousex >= ResX / 4 - 70 && mousex <= ResX / 4 + 70 ) && ( mousey >= 350 ) && ( mousey <= 380 ) ) {
							al_draw_text ( Fuente, al_map_rgb ( 250, 250, 110 ), ResX / 4, 330, ALLEGRO_ALIGN_CENTRE, "Regresar" );
							{
								if ( eventossub.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
								{
									if ( eventossub.mouse.button & 1 ) {
										submenu = false;
										break;
									}
								}
							}
							submenu = true;
						}
						al_flip_display ( );
					}
					submenu = true;
					
				}
			}
		}
		if ( ( mousex >= ResX / 2 - 30 && mousex <= ResX / 2 + 30 ) && ( mousey >= 260 ) && ( mousey <= 280 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 2, 250, ALLEGRO_ALIGN_CENTRE, "Instrucciones" );
			if ( eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( eventos.mouse.button & 1 ) {
					while ( instr ) {
						ALLEGRO_EVENT eventos2;
						al_wait_for_event ( cola_eventos, &eventos2 );
						if ( eventos2.type == ALLEGRO_EVENT_MOUSE_AXES )
						{
							mousex = eventos2.mouse.x;
							mousey = eventos2.mouse.y;

						}
						if ( eventos2.type == ALLEGRO_EVENT_TIMER )
						{
							//al_wait_for_event(cola_eventos, &eventos);
							if ( eventos2.timer.source == timer )
							{
								al_clear_to_color ( al_map_rgb ( 0, 0, 0 ) );
								al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 2, 100, ALLEGRO_ALIGN_CENTRE, "INSTRUCCIONES" );
								//al_draw_filled_rectangle(370, 210, 430, 230, al_map_rgb(200, 50, 50));
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 200, ALLEGRO_ALIGN_CENTRE, "Movimiento: WASD/Flechas" );
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 2, 250, ALLEGRO_ALIGN_CENTRE, "Disparo: ESPACIO" );
								al_draw_text ( Fuente, al_map_rgb ( 250, 250, 250 ), ResX / 4, 350, ALLEGRO_ALIGN_CENTRE, "Salir" );
							}
						}
						if ( ( mousex >= ResX / 4 - 30 && mousex <= ResX / 4 + 30 ) && ( mousey >= 350 ) && ( mousey <= 380 ) ) {
							al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 4, 350, ALLEGRO_ALIGN_CENTRE, "Salir" );
							{
								if ( eventos2.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
								{
									if ( eventos2.mouse.button & 1 ) {
										instr = false;
										break;
									}
								}
							}
						}
						al_flip_display ( );
					}
					instr = true;
				}
			}
		}
		if ( ( mousex >= ResX / 2 - 30 && mousex <= ResX / 2 + 30 ) && ( mousey >= 350 ) && ( mousey <= 380 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), ResX / 2, 350, ALLEGRO_ALIGN_CENTRE, "Salir" );
			{
				if ( eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
				{
					if ( eventos.mouse.button & 1 ) {
						hecho = false;
						break;
					}
				}
			}
		}
		al_flip_display ( );
	}
	al_destroy_event_queue ( cola_eventos );
	al_destroy_font ( Fuente );
	al_destroy_font ( Fuente2 );
	al_destroy_timer ( timer );
	al_destroy_display ( pantalla );
}
