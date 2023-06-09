$(document).ready(function() {
  var batteryPercentage = parseInt($("#battery-percentage").text());

  if (batteryPercentage >= 90) {
    $("#battery-icon").html('<i class="fas fa-battery-full"></i>');
  } else if (batteryPercentage >= 60) {
    $("#battery-icon").html('<i class="fas fa-battery-three-quarters"></i>');
  } else if (batteryPercentage >= 30) {
    $("#battery-icon").html('<i class="fas fa-battery-half"></i>');
  } else if (batteryPercentage >= 10) {
    $("#battery-icon").html('<i class="fas fa-battery-quarter"></i>');
  } else {
    $("#battery-icon").html('<i class="fas fa-battery-empty"></i>');
  }
});
