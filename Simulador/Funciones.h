#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


using namespace std;
#pragma warning(disable:4996);
#define FPS 30.0
#pragma once


typedef struct vehiculo {
	int x;
	int y;
	ALLEGRO_BITMAP * imagen;
	int peso;
	int dimension;
	int ID;
	bool estado;

}*Ptr_vehiculo;

typedef struct espacioEstacionamiento {
	int pesoPermitido;
	int dimensionPermitida;
	int numeroEspacio;
	bool disponible;
	Ptr_vehiculo vehiculoAparcado;
	espacioEstacionamiento * siguiente;

}*Ptr_espacioEstacionamiento;

Ptr_espacioEstacionamiento CrearEspacio ( int num, int pesoPermitido, int dimensionPermitida ) {

	Ptr_espacioEstacionamiento nuevo = new( espacioEstacionamiento );
	nuevo->numeroEspacio = num;
	nuevo->disponible = true;
	nuevo->dimensionPermitida = dimensionPermitida;
	nuevo->pesoPermitido = pesoPermitido;
	nuevo->siguiente = NULL;

	nuevo->vehiculoAparcado = new ( vehiculo );
	nuevo->vehiculoAparcado->estado = false;
	nuevo->vehiculoAparcado->imagen = NULL;
	nuevo->vehiculoAparcado->x = 0;
	nuevo->vehiculoAparcado->y = 0;
	nuevo->vehiculoAparcado->peso = 0;
	nuevo->vehiculoAparcado->dimension = 0;
	nuevo->vehiculoAparcado->ID = num;

	return nuevo;

}

void AgregarFinalLista ( Ptr_espacioEstacionamiento & Lista, Ptr_espacioEstacionamiento & Nuevo )
{
	Ptr_espacioEstacionamiento Aux;
	Aux = Lista;
	if ( Aux != NULL )
	{
		while ( Aux->siguiente != NULL )
		{
			Aux = Aux->siguiente;
		}

		Aux->siguiente = Nuevo;
	}
	else
	{
		Lista = Nuevo;
	}


}

void destruirEstacionamiento ( Ptr_espacioEstacionamiento & estacionamiento ) {

	while ( estacionamiento != NULL ) {
		Ptr_espacioEstacionamiento aux = estacionamiento;
		estacionamiento = estacionamiento->siguiente;

		// Si el espacio tiene un vehículo asignado, libera la memoria del vehículo
		if ( aux->vehiculoAparcado != NULL ) {
			cout << "borrando vehiculo" << endl;
			delete ( aux->vehiculoAparcado );
			aux->vehiculoAparcado = NULL; // Asegurarse de evitar el uso de punteros colgantes
		}

		// Finalmente, libera la memoria del nodo de estacionamiento
		cout << "eliminando espacio de estacionamiento" << endl;
		delete ( aux );

	}
}

void pintarNodos ( Ptr_espacioEstacionamiento & estacionamiento ) {
	Ptr_espacioEstacionamiento aux = estacionamiento;
	while ( aux != NULL ) {
		cout << "pintado un nodo" << endl;
		cout << aux->vehiculoAparcado << endl;
		cout << aux->vehiculoAparcado->imagen << "esto es imagen" << endl;

		aux = aux->siguiente;
	}

}

void inicializarEstacionamiento ( Ptr_espacioEstacionamiento & estacionamiento, int cantidad ) {
	int pesoPermitido;
	double dimensionPermitida;

	estacionamiento = NULL;
	for ( int i = 1; i <= cantidad; i++ )
	{
		if ( i < cantidad * 1 / 5 ) {
			pesoPermitido = 8300;
			dimensionPermitida = 6.25;
		}
		else if ( i < cantidad * 2 / 5 ) {
			pesoPermitido = 2200;
			dimensionPermitida = 5.32;
		}
		else if ( i < cantidad * 3 / 5 ) {
			pesoPermitido = 1200;
			dimensionPermitida = 4.31;
		}
		else if ( i < cantidad * 4 / 5 ) {
			pesoPermitido = 800;
			dimensionPermitida = 3.71;
		}
		else {
			pesoPermitido = 200;
			dimensionPermitida = 1.8;
		}
		Ptr_espacioEstacionamiento nuevoEspacio = CrearEspacio ( i, pesoPermitido, dimensionPermitida );
		AgregarFinalLista ( estacionamiento, nuevoEspacio );

	}
}

Ptr_espacioEstacionamiento buscarNodo ( Ptr_espacioEstacionamiento & estacionamiento, int buscar ) {
	Ptr_espacioEstacionamiento aux = estacionamiento;
	while ( aux != NULL ) {
		if ( aux->numeroEspacio == buscar ) {
			return aux;
		}
		aux = aux->siguiente;
	}

}

void actualizarInfoVehiculo ( Ptr_espacioEstacionamiento & nodo, ALLEGRO_BITMAP *& pesado, ALLEGRO_BITMAP *& ligero, ALLEGRO_BITMAP *& todoTerreno, ALLEGRO_BITMAP *& coupe, ALLEGRO_BITMAP *& hatchback ) {
	nodo->disponible = false;
	switch ( nodo->pesoPermitido ) {
	case 8300:
		nodo->vehiculoAparcado->dimension = 6.00;
		nodo->vehiculoAparcado->peso = 8100;
		nodo->vehiculoAparcado->ID = nodo->numeroEspacio;
		nodo->vehiculoAparcado->imagen = pesado;
		break;
	case 2200:
		nodo->vehiculoAparcado->dimension = 5.00;
		nodo->vehiculoAparcado->peso = 2000;
		nodo->vehiculoAparcado->ID = nodo->numeroEspacio;
		nodo->vehiculoAparcado->imagen = todoTerreno;
		break;
	case 1200:
		nodo->vehiculoAparcado->dimension = 4.00;
		nodo->vehiculoAparcado->peso = 1000;
		nodo->vehiculoAparcado->ID = nodo->numeroEspacio;
		nodo->vehiculoAparcado->imagen = hatchback;
		break;
	case 800:
		nodo->vehiculoAparcado->dimension = 3.50;
		nodo->vehiculoAparcado->peso = 500;
		nodo->vehiculoAparcado->ID = nodo->numeroEspacio;
		nodo->vehiculoAparcado->imagen = coupe;
		break;
	case 200:
		nodo->vehiculoAparcado->dimension = 1.00;
		nodo->vehiculoAparcado->peso = 150;
		nodo->vehiculoAparcado->ID = nodo->numeroEspacio;
		nodo->vehiculoAparcado->imagen = ligero;
		break;
	}

}

bool verificarDisponibilidad ( Ptr_espacioEstacionamiento & nodo ) {
	return nodo->disponible;

}

void llenarEstacionamiento ( Ptr_espacioEstacionamiento & estacionamiento, int porcentaje, int totalEspacios, ALLEGRO_BITMAP *& pesado, ALLEGRO_BITMAP *& ligero, ALLEGRO_BITMAP *& todoTerreno, ALLEGRO_BITMAP *& coupe, ALLEGRO_BITMAP *& hatchback ) {
	int espacios_a_completar = ( totalEspacios * porcentaje ) / 100;
	int espacioABuscar = 0;
	int vehiculosAparcados = 0;
	Ptr_espacioEstacionamiento nodo = estacionamiento;
	while ( vehiculosAparcados < espacios_a_completar )
	{
		espacioABuscar = 1 + rand ( ) % totalEspacios;
		nodo = buscarNodo ( estacionamiento, espacioABuscar );
		while ( !verificarDisponibilidad ( nodo ) ) {
			espacioABuscar = 1 + rand ( ) % totalEspacios;
			nodo = buscarNodo ( estacionamiento, espacioABuscar );
		}
		actualizarInfoVehiculo ( nodo, pesado, ligero, todoTerreno, coupe, hatchback );
		vehiculosAparcados++;
	}
}

void recibir_parametros ( int & ocupacion, int & cantidadEspacios ) {
	ALLEGRO_DISPLAY * display_param = al_create_display ( 500, 300 );
	if ( !display_param ) {
		fprintf ( stderr, "Failed to create display.\n" );
		return;
	}

	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue ( );
	ALLEGRO_FONT * font = al_load_font ( "pixel.ttf", 40, NULL );

	al_register_event_source ( event_queue, al_get_keyboard_event_source ( ) );
	al_register_event_source ( event_queue, al_get_display_event_source ( display_param ) );

	char num_input[4] = {0};
	int pos = 0;
	bool info = false;
	bool capturingOcupacion = true;  // Indica si estamos capturando la ocupación o la cantidad de espacios

	al_clear_to_color ( al_map_rgb ( 0, 0, 0 ) );
	al_draw_text ( font, al_map_rgb ( 255, 255, 255 ), 270, 100, ALLEGRO_ALIGN_CENTER, "Ingrese la ocupacion inicial:" );
	al_flip_display ( );

	while ( !info ) {
		ALLEGRO_EVENT event;
		al_wait_for_event ( event_queue, &event );

		if ( event.type == ALLEGRO_EVENT_KEY_CHAR ) {
			if ( event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && pos > 0 ) {
				pos--;
				num_input[pos] = '\0';
			}
			else if ( event.keyboard.keycode == ALLEGRO_KEY_ENTER ) {
				int valor = atoi ( num_input );
				if ( valor >= 0 && valor <= 100 ) {
					if ( capturingOcupacion ) {
						ocupacion = valor;
						capturingOcupacion = false;  // Cambiar a capturar la cantidad de espacios
						strcpy ( num_input, "" );  // Limpiar el buffer
						pos = 0;
						al_draw_text ( font, al_map_rgb ( 255, 255, 255 ), 270, 100, ALLEGRO_ALIGN_CENTER, "Ingrese cantidad de espacios:" );
					}
					else {
						cantidadEspacios = valor;
						info = true;  // Finaliza la captura de ambos valores
					}
				}
				else {
					al_show_native_message_box ( display_param, "Error", "Valores incorrectos",
						"Debes ingresar un valor entre 0 y 100.", NULL, ALLEGRO_MESSAGEBOX_ERROR );
					strcpy ( num_input, "" );  // Limpiar el buffer si hay error
					pos = 0;
				}
			}
			else if ( event.keyboard.unichar >= '0' && event.keyboard.unichar <= '9' && pos < 3 ) {
				num_input[pos] = event.keyboard.unichar;
				pos++;
				num_input[pos] = '\0';
			}
		}

		al_clear_to_color ( al_map_rgb ( 0, 0, 0 ) );
		al_draw_text ( font, al_map_rgb ( 255, 255, 255 ), 270, 100, ALLEGRO_ALIGN_CENTER,
			capturingOcupacion ? "Ingrese la ocupacion inicial:" : "Ingrese cantidad de espacios:" );
		al_draw_text ( font, al_map_rgb ( 255, 255, 255 ), 250, 150, ALLEGRO_ALIGN_CENTER, num_input );
		al_flip_display ( );

		if ( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
			break;
		}
	}

	al_destroy_display ( display_param );
	al_destroy_event_queue ( event_queue );
	al_destroy_font ( font );
}

void mostrarVehiculo ( ALLEGRO_BITMAP *& carro, int & posX, int & posY, bool &mostrable ) {
	
	if ( posX < 550 ) { al_draw_bitmap ( carro, posX, posY, 0 ); posX += 20; }
	else if ( posX > 500 && posY>200) { al_draw_bitmap ( carro, posX, posY, ALLEGRO_FLIP_HORIZONTAL ); posY -= 10; }
	else if ( posX > 500 && posY > 190 ) { posX = 20; posY = 350; mostrable = false; }
}

void juego_una_planta_un_piso ( int ocupacion, int espacios ) {

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


	ALLEGRO_EVENT_QUEUE * cola_eventos = al_create_event_queue ( );

	ALLEGRO_TIMER * timer = al_create_timer ( 10.0 / FPS );
	ALLEGRO_BITMAP * Fondo = al_load_bitmap ( "Imagenes\\fondo_entrada.png" );
	ALLEGRO_BITMAP * pesado = al_load_bitmap ( "Imagenes\\pesado.png" );
	ALLEGRO_BITMAP * ligero = al_load_bitmap ( "Imagenes\\ligero.png" );
	ALLEGRO_BITMAP * todoTerreno = al_load_bitmap ( "Imagenes\\todoTerreno.png" );
	ALLEGRO_BITMAP * coupe = al_load_bitmap ( "Imagenes\\coupe.png" );
	ALLEGRO_BITMAP * hatchback = al_load_bitmap ( "Imagenes\\hatchback.png" );


	ALLEGRO_FONT * Fuente = al_load_font ( "pixel.ttf", 40, NULL );
	ALLEGRO_FONT * Fuente2 = al_load_font ( "pixel.ttf", 20, NULL );


	al_register_event_source ( cola_eventos, al_get_timer_event_source ( timer ) );
	al_register_event_source ( cola_eventos, al_get_keyboard_event_source ( ) );
	al_register_event_source ( cola_eventos, al_get_mouse_event_source ( ) );


	bool hecho = true;
	int cont = 1;
	char bufferCont[4] = {0};
	int largo_texto;
	int posmousex = 0;
	int posmousey = 0;
	bool hoverLigeros = false;
	bool hoverCoupe = false;
	bool hoverHatchback = false;
	bool hoverTodoTerreno = false;
	bool hoverPesados = false;
	bool aparcandoLigero = false;
	bool aparcandoCoupe = false;
	bool aparcandoHatchback = false;
	bool aparcandoTodoterreno = false;
	bool aparcandoPesado = false;
	itoa ( ocupacion, bufferCont, 10 );
	Ptr_espacioEstacionamiento estacionamiento;
	Ptr_vehiculo nuevo;
	int posX = 20;
	int posY = 350;

	al_start_timer ( timer );
	inicializarEstacionamiento ( estacionamiento, espacios );
	llenarEstacionamiento ( estacionamiento, ocupacion, espacios, pesado, ligero, todoTerreno, coupe, hatchback );
	//pintarNodos ( estacionamiento );

	while ( hecho ) {

		ALLEGRO_EVENT evento;
		al_wait_for_event ( cola_eventos, &evento );
		if ( evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
			hecho = false;
		}
		if ( evento.type == ALLEGRO_EVENT_MOUSE_AXES )
		{
			posmousex = evento.mouse.x;
			posmousey = evento.mouse.y;
			hoverLigeros = ( posmousex >= 68 && posmousex <= 167 ) && ( posmousey >= 455 && posmousey <= 485 );
			hoverCoupe = ( posmousex >= 195 && posmousex <= 275 ) && ( posmousey >= 455 && posmousey <= 485 );
			hoverHatchback = ( posmousex >= 295 && posmousex <= 430 ) && ( posmousey >= 455 && posmousey <= 485 );
			hoverTodoTerreno = ( posmousex >= 445 && posmousex <= 620 ) && ( posmousey >= 455 && posmousey <= 485 );
			hoverPesados = ( posmousex >= 635 && posmousex <= 745 ) && ( posmousey >= 455 && posmousey <= 485 );

		}
		if ( ( posmousex >= 68 && posmousex <= 167 ) && ( posmousey >= 455 ) && ( posmousey <= 485 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), 65, 450, ALLEGRO_ALIGN_LEFT, "Ligeros" );
			if ( evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( evento.mouse.button & 1 ) {
					aparcandoLigero = aparcandoCoupe = aparcandoHatchback = aparcandoTodoterreno = aparcandoPesado = false;
					aparcandoLigero = true;

				}
			}
		}
		if ( ( posmousex >= 195 && posmousex <= 275 ) && ( posmousey >= 455 ) && ( posmousey <= 485 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), 190, 450, ALLEGRO_ALIGN_LEFT, "Coupe" );
			if ( evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( evento.mouse.button & 1 ) {
					aparcandoLigero = aparcandoCoupe = aparcandoHatchback = aparcandoTodoterreno = aparcandoPesado = false;
					aparcandoCoupe = true;

				}
			}
		}
		if ( ( posmousex >= 295 && posmousex <= 430 ) && ( posmousey >= 455 ) && ( posmousey <= 485 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), 290, 450, ALLEGRO_ALIGN_LEFT, "Hatchback" );
			if ( evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( evento.mouse.button & 1 ) {
					aparcandoLigero = aparcandoCoupe = aparcandoHatchback = aparcandoTodoterreno = aparcandoPesado = false;
					aparcandoHatchback = true;

				}
			}
		}
		if ( ( posmousex >= 445 && posmousex <= 620 ) && ( posmousey >= 455 ) && ( posmousey <= 485 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), 440, 450, ALLEGRO_ALIGN_LEFT, "Todo terreno" );
			if ( evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( evento.mouse.button & 1 ) {
					aparcandoLigero = aparcandoCoupe = aparcandoHatchback = aparcandoTodoterreno = aparcandoPesado = false;
					aparcandoTodoterreno = true;

				}
			}
		}
		if ( ( posmousex >= 635 && posmousex <= 745 ) && ( posmousey >= 455 ) && ( posmousey <= 485 ) ) {
			al_draw_text ( Fuente, al_map_rgb ( 250, 220, 110 ), 630, 450, ALLEGRO_ALIGN_LEFT, "Pesados" );
			if ( evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
			{
				if ( evento.mouse.button & 1 ) {
					aparcandoLigero = aparcandoCoupe = aparcandoHatchback = aparcandoTodoterreno = aparcandoPesado = false;
					aparcandoPesado = true;

				}
			}
		}
		if ( evento.type == ALLEGRO_EVENT_KEY_UP )
		{
			switch ( evento.keyboard.keycode ) {
			case ALLEGRO_KEY_ESCAPE:
				hecho = false;
				break;
			}

		}
		if ( evento.type == ALLEGRO_EVENT_TIMER )
		{
			if ( evento.timer.source == timer )
			{
				al_clear_to_color ( al_map_rgb ( 0, 0, 0 ) );
				al_draw_scaled_bitmap ( Fondo, 0, 0, 626, 470, 0, 0, 800, 500, NULL );
				al_draw_filled_rounded_rectangle ( 635, 20, 795, 40, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_filled_rounded_rectangle ( 3, 10, 200, 50, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_text ( Fuente2, al_map_rgb ( 250, 200, 50 ), 790, 20, ALLEGRO_ALIGN_RIGHT, "Presione ESC para salir" );
				al_draw_text ( Fuente, al_map_rgb ( 250, 200, 50 ), 10, 10, ALLEGRO_ALIGN_LEFT, "Ocupacion:" );
				al_draw_text ( Fuente, al_map_rgb ( 250, 200, 50 ), 140, 10, ALLEGRO_ALIGN_LEFT, bufferCont );
				largo_texto = al_get_text_width ( Fuente, bufferCont );
				al_draw_text ( Fuente, al_map_rgb ( 250, 200, 50 ), 130 + largo_texto + 2, 10, ALLEGRO_ALIGN_LEFT, " % " );
				al_draw_filled_rounded_rectangle ( 55, 455, 160, 485, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_filled_rounded_rectangle ( 180, 455, 265, 488, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_filled_rounded_rectangle ( 280, 455, 420, 485, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_filled_rounded_rectangle ( 430, 455, 610, 485, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_filled_rounded_rectangle ( 620, 455, 735, 485, 10, 10, al_map_rgba ( 0, 0, 0, 190 ) );
				al_draw_text ( Fuente, hoverLigeros ? al_map_rgb ( 250, 220, 110 ) : al_map_rgb ( 250, 250, 250 ), 65, 450, ALLEGRO_ALIGN_LEFT, "Ligeros" );
				al_draw_text ( Fuente, hoverCoupe ? al_map_rgb ( 250, 220, 110 ) : al_map_rgb ( 250, 250, 250 ), 190, 450, ALLEGRO_ALIGN_LEFT, "Coupe" );
				al_draw_text ( Fuente, hoverHatchback ? al_map_rgb ( 250, 220, 110 ) : al_map_rgb ( 250, 250, 250 ), 290, 450, ALLEGRO_ALIGN_LEFT, "Hatchback" );
				al_draw_text ( Fuente, hoverTodoTerreno ? al_map_rgb ( 250, 220, 110 ) : al_map_rgb ( 250, 250, 250 ), 440, 450, ALLEGRO_ALIGN_LEFT, "Todo terreno" );
				al_draw_text ( Fuente, hoverPesados ? al_map_rgb ( 250, 220, 110 ) : al_map_rgb ( 250, 250, 250 ), 630, 450, ALLEGRO_ALIGN_LEFT, "Pesados" );
				if ( aparcandoLigero ) mostrarVehiculo ( ligero, posX, posY ,aparcandoLigero);
				if ( aparcandoCoupe ) mostrarVehiculo ( coupe, posX, posY , aparcandoCoupe);
				if ( aparcandoHatchback ) mostrarVehiculo ( hatchback, posX, posY ,aparcandoHatchback);
				if ( aparcandoTodoterreno ) mostrarVehiculo ( todoTerreno, posX, posY , aparcandoTodoterreno);
				if ( aparcandoPesado ) mostrarVehiculo ( pesado, posX, posY , aparcandoPesado);


			}
		}
		al_flip_display ( );
	}
	//pintarNodos ( estacionamiento );
	destruirEstacionamiento ( estacionamiento );
	al_destroy_event_queue ( cola_eventos );
	al_destroy_font ( Fuente );
	al_destroy_font ( Fuente2 );
	al_destroy_timer ( timer );
}
