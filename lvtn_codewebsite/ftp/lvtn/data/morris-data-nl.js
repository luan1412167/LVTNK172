$(function() {
    $.get("../esp01/dongdien/jsonnl.php", function(data, status){
        data=JSON.parse(data);
        Morris.Area({
            element: 'morris-area-chart2',
            data: data,
            xkey: ['period'],
            ykeys: ['nangluong'],
            labels: ['nangluong'],
            behaveLikeLine: true,
            pointSize: 1,
            fillOpacity: 0.6,
            hideHover: 'auto',
            ymin:19100,
            pointFillColors:['#ffffff'],
            lineColors:['red'],
          resize: true
        });
    });
});

    