$(function() {

    Morris.Area({
        element: 'morris-area-chart',
        data: [{
            period: '1',
            iphone: 2666,
        }, {
            period: '2',
            iphone: 2778,
        }, {
            period: '3',
            iphone: 4912,
        }, {
            period: '4',
            iphone: 3767,
        }, {
            period: '5',
            iphone: 6810,
        }, {
            period: '6',
            iphone: 5670,
        }, {
            period: '7',
            iphone: 4820,
        }, {
            period: '8',
            iphone: 15073,
        }, {
            period: '9',
            iphone: 10687,
        }, {
            period: '10',
            iphone: 8432,
        }],
        xkey: 'period',
        ykeys: ['iphone'],
        labels: ['iPhone'],
        pointSize: 2,
        hideHover: 'auto',
        resize: true
    });

    Morris.Donut({
        element: 'morris-donut-chart',
        data: [{
            label: "Download Sales",
            value: 12
        }, {
            label: "In-Store Sales",
            value: 30
        }, {
            label: "Mail-Order Sales",
            value: 20
        }],
        resize: true
    });

    Morris.Bar({
        element: 'morris-bar-chart',
        data: [{
            y: '2006',
            a: 100,
            b: 90
        }, {
            y: '2007',
            a: 75,
            b: 65
        }, {
            y: '2008',
            a: 50,
            b: 40
        }, {
            y: '2009',
            a: 75,
            b: 65
        }, {
            y: '2010',
            a: 50,
            b: 40
        }, {
            y: '2011',
            a: 75,
            b: 65
        }, {
            y: '2012',
            a: 100,
            b: 90
        }],
        xkey: 'y',
        ykeys: ['a', 'b'],
        labels: ['Series A', 'Series B'],
        hideHover: 'auto',
        resize: true
    });
    
});
