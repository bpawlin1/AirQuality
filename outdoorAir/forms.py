from django import forms
from .models import outdoorAir, shedWeather

class outdoorAirForm(forms.ModelForm):
    class Meta:
        model = outdoorAir
        fields = ( 'device','humidityReading','bmpTemp','bmpPressure','bmpAltitude','pm25Reading','pm10Reading','batt_volt','batt_perc', 'co2')
class shedWeatherForm(forms.ModelForm):
    class Meta:
        model = shedWeather
        fields = ( 'device','bme_temp','bme_humidity','bme_pressure','bme_altitude','bme_gas','pm_1','pm_25','pm_10', 'batt_volt', 'batt_perc')

    #id = forms.IntegerField()
    #device = forms.CharField()
    #dt = forms.DateTimeField(
    #input_formats = ['%Y-%m-%dT%H:%M'],
    #widget = forms.DateTimeInput(
    #    attrs={
    #        'type': 'datetime-local',
    #        'class': 'form-control'},
    #    format='%Y-%m-%dT%H:%M'))
    #scd30_temp = forms.FloatField()
    #CO2 = forms.FloatField()
    #CO2_rating = forms.CharField(max_length=25)
    #bme_temp = forms.FloatField()
    #bme_humidity = forms.FloatField()
    #bme_gas = forms.FloatField()
    #bme_pressure = forms.FloatField()
    #bme_altitude = forms.FloatField()
    #PM10 = forms.FloatField()
    #pm25 = forms.FloatField()
    #PM100 = forms.FloatField()