from django.db import models
from django.utils import timezone

# Create your models here.
class outdoorAir(models.Model):
    id = models.AutoField(primary_key=True)
    device = models.CharField(max_length=100)
    dt = models.DateTimeField(default=timezone.now)
    humidityReading = models.FloatField()
    bmpTemp = models.FloatField()
    bmpPressure = models.FloatField()
    bmpAltitude = models.FloatField()
    pm25Reading = models.FloatField()
    pm10Reading = models.FloatField()
    batt_volt = models.FloatField()
    batt_perc = models.FloatField()
    co2 = models.FloatField()

class shedWeather(models.Model):
    id = models.AutoField(primary_key=True)
    device = models.CharField(max_length=100)
    dt = models.DateTimeField(default=timezone.now)
    bme_temp = models.FloatField()
    bme_humidity = models.FloatField()
    bme_pressure = models.FloatField()
    bme_altitude = models.FloatField()
    bme_gas = models.FloatField()
    pm_1 = models.FloatField()
    pm_25 = models.FloatField()
    pm_10 = models.FloatField()
    batt_volt = models.FloatField()
    batt_perc = models.FloatField()