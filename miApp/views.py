from django.shortcuts import render, redirect
# Descargar módulo requests via pip
import requests

# Create your views here.

# Variable: Dirección IP de mi ESP32
ESP32IP = 'http://19X.XXX.X.XX'

def index(request):
    if request.method == 'POST':
        comando = request.POST.get('command')

        # 1 LED on 2 LED off
        if comando == '1':
            try:
                # Acceder la ruta HTTP del HTTP server. Esto se hace usando 'serial', con la IP Adress
                requests.get(f'{ESP32IP}/led/on')
            except requests.RequestException as e:
                # Imprimir error (request failed)
                print(f'Error enviando peticion de encendido al ESP32: {e}')
        
        elif comando == '2':
            try:
                # Acceder la ruta HTTP del HTTP server. Esto se hace usando 'serial', con la IP Adress
                requests.get(f'{ESP32IP}/led/off')
            except requests.RequestException as e:
                # Imprimir error (request failed)
                print(f'Error enviando peticion de apagado al ESP32: {e}')
        
        # Redireccionar a la página default
        return redirect('/')
    return render(request, 'miApp/index.html', {})