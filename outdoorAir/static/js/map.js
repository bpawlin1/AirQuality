require([
    "esri/Map",
    "esri/views/MapView",
    "esri/Graphic",
    "esri/geometry/Circle",
    "esri/widgets/Popup"
  ], function(Map, MapView, Graphic, Circle, Popup) {
    // Define the color ranges and corresponding colors
    const colorRanges = [
      { max: 12.0, color: [0, 255, 0, 0.7] },     // Good (Green)
      { max: 35.5, color: [255, 255, 0, 0.7] },  // Moderate (Yellow)
      { max: 55.5, color: [255, 165, 0, 0.7] },  // Unhealthy for Sensitive Groups (Orange)
      { max: 150.5 , color: [255, 0, 0, 0.7] },     // Unhealthy (Red)
      { max: 250.5  , color: [128, 0, 128, 0.7] },   // Very Unhealthy (Purple)
      { max: 500.4, color: [128, 0, 0, 0.7] }  // Hazardous (Maroon)
    ];
  
    // Function to get color based on PM reading
    function getColorFromPMReading(pmReading) {
      for (const range of colorRanges) {
        if (pmReading <= range.max) {
          return range.color;
        }
      }
      return [0, 0, 0, 0.7]; // Default color if no range matches
    }
  
    // Create a map
    var map = new Map({
      basemap: "hybrid"
    });
  
    // Create a map view
    var view = new MapView({
      container: "viewDiv",
      map: map,
      center: [-76.70731845212603, 39.99530048434682],
      zoom: 19
    });
  
    // Get the pm-reading value
    var pmReadingElement = document.getElementById('pm-reading');
    var pmReading = pmReadingElement.textContent || pmReadingElement.innerText;
  
    // Define the circle center point and radius
    var center = {
      x: -76.70731845212603,
      y: 39.99530048434682,
      spatialReference: { wkid: 4326 } // Assuming WGS84 coordinate system
    };
    var radius = 10; // Example radius in meters
  
    // Create a circle geometry
    var circle = new Circle({
      center: center,
      radius: radius
    });
  
    // Create the circle graphic with color based on the PM reading
    var graphic = new Graphic({
      geometry: circle,
      symbol: {
        type: "simple-fill",
        color: getColorFromPMReading(pmReading),
        outline: {
          color: [255, 255, 255, 0.5],
          width: 1
        }
      }
    });

    // Create the text symbol for the label
var textSymbol = {
    type: "text",
    color: [255, 255, 255],
    haloColor: [0, 0, 0],
    haloSize: "1px",
    text: "PM1\n" + pmReading.toString(),
    font: {
      size: "12px",
      weight: "bold"
    }
  };
  
  // Create the label graphic
  var labelGraphic = new Graphic({
    geometry: circle.center,
    symbol: textSymbol
  });

    view.graphics.addMany([graphic, labelGraphic]);
  // Set the PM reading value as an attribute on the graphic

  });
  