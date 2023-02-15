from django.urls import path
from outdoorAir import views

urlpatterns = [
    path('', views.index, name='index'),
    path('graph/', views.graph, name='graph'),
    path('addOutdoorAir/', views.addOutdoorAir, name='addOutdoorAir'),
    path('addShedWeather/', views.addShedWeather, name='addShedWeather'),
]