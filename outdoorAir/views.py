from django.shortcuts import render, redirect
from .forms import outdoorAirForm, shedWeatherForm
from django.views.decorators.csrf import csrf_protect, csrf_exempt
from outdoorAir.models import shedWeather
from django.http import JsonResponse, HttpResponse
from collections import Counter
from math import ceil

def index(request):
    last_entry = shedWeather.objects.last()
    print(last_entry)
    context = {
    'last_entry': last_entry,
    } 
    return render(request, 'index.html', context=context)


def graph(request):
    labels = []
    data = []
    stats = shedWeather.objects.order_by('dt')

    for row in stats:
        labels.append(row.dt)
        data.append(row.bme_temp) 
        
    return render(request, 'graph.html', {
        'labels': labels,
        'values': data,
    })

@csrf_exempt
def addOutdoorAir(request):
    print(request.POST)
    form = outdoorAirForm(request.POST)
    form.save()
    #if request.method == "POST":
#
    #    if form.is_valid():
    #        post = form.save()
    #        post.save()
    #        return redirect('index')
    #else:
    #    form = outdoorAirForm()
    return render(request, 'addOutdoorAir.html', {'form': form})

@csrf_exempt
def addShedWeather(request):
    if request.method == 'POST':
        print(request.POST)
        form = shedWeatherForm(request.POST)
        if form.is_valid():
            form.save()
    else:
        form = shedWeatherForm() 

    return render(request, 'addShedWeather.html', {'form': form})