from django.urls import path
from outdoorAir import views

urlpatterns = [
    path('', views.home, name='index'),
    path('addOutdoorAir/', views.addOutdoorAir, name='addOutdoorAir'),
    path('addShedWeather/', views.addShedWeather, name='addShedWeather'),
]