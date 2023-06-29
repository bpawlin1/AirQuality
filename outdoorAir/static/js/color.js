$(document).ready(function() {
    // Retrieve the PM value
    var pm1Value = parseFloat($("#pm1-value").text());
    var pm25Value = parseFloat($("#pm25-value").text());
    var pm10Value = parseFloat($("#pm10-value").text());
    // Add color coding based on the PM  values
    if ((0.0 <= pm1Value && pm1Value <= 12.0) || (0.0 <= pm25Value && pm25Value <= 12.0) || (0.0 <= pm10Value && pm10Value <= 12.0))  {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Good");
    } else if ((12.1<= pm1Value && pm1Value <= 35.4) || (12.1 <= pm25Value && pm25Value <= 35.4) || (12.1 <= pm10Value && pm10Value <= 35.4)) {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Moderate");
    } else if ((35.5 <= pm1Value && pm1Value <= 55.4) || (35.5 <= pm25Value && pm25Value <= 55.4) || (35.5 <= pm10Value && pm10Value <= 55.4)) {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Unhealthy_for_Sensitive_Groups");
    } else if ((55.5 <= pm1Value && pm1Value <= 150.4) || (55.5 <= pm25Value && pm25Value <= 150.4)  || (55.5 <= pm10Value && pm10Value <= 150.4) ) {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Unhealthy");
    } else if ((150.5 <= pm1Value && pm1Value <= 250.4) || (150.5 <= pm25Value && pm25Value <= 250.4) || (150.5 <= pm10Value && pm10Value <= 250.4)){
        $("#pm-card, #pm-card25, #pm-card10").addClass("Very_Unhealthy");
    } else if ((250.5 <= pm1Value && pm1Value <= 350.4) || (250.5 <= pm25Value && pm25Value <= 350.4) || (250.5 <= pm10Value && pm10Value <= 350.4)) {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Hazardous");
    } else if ((350.5 <= pm1Value && pm1Value <= 500.4) || (350.5 <= pm25Value && pm25Value <= 500.4) || (350.5 <= pm10Value && pm10Value <= 500.4)) {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Vey_Hazardous");
    } else {
        $("#pm-card, #pm-card25, #pm-card10").addClass("Invalid");
    }

    var batteryPercentage = parseInt($("#battery-percentage").text());

});
