$(function() {
    $.get("../esp01/dongdien/json.php", function(data, status){
        data=JSON.parse(data);
        Morris.Area({
            element: 'morris-area-chart1',
            data: data,
            xkey: ['period'],
            ykeys: ['congsuat'],
            labels: ['congsuat'],
            behaveLikeLine: true,
            pointSize: 1,
            fillOpacity: 0.6,
            hideHover: 'auto',
            
            pointFillColors:['#ffffff'],
            lineColors:['red'],
            ymin: 0,
            ymax: 5,
          resize: true
        });
    });
});

    
  
