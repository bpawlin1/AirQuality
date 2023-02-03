from django.contrib import admin
from outdoorAir.models import outdoorAir, shedWeather
# Register your models here.


class outdoorAirAdmin(admin.ModelAdmin):
    list_display = [field.name for field in outdoorAir._meta.get_fields()]

class shedWeatherAdmin(admin.ModelAdmin):
    list_display = [field.name for field in shedWeather._meta.get_fields()]



admin.site.register(outdoorAir, outdoorAirAdmin)
admin.site.register(shedWeather, shedWeatherAdmin)
