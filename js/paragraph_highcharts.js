
/**
 * @file
 * Javascript for paragraph highcharts.
 */

(function($) {
    Drupal.behaviors.entityBackgroundHighcharts = {
        attach: function(context) {
            var highcharts = Drupal.settings.paragraph_highcharts
            $.each(highcharts, function(selector, settings) {
                $(selector).highcharts({
                    chart: {
                        type: settings.chart.type
                    },
                    title: {
                        text: settings.title.text,
                        x: settings.title.x
                    },
                    subtitle: {
                        text: settings.subtitle.text,
                        x: settings.subtitle.x
                    },
                    xAxis: {
                        categories: settings.xAxis.categories
                    },
                    yAxis: {
                        title: {
                            text: settings.yAxis.title.text
                        }
                    },
                    legend: {
                        layout: 'vertical',
                        align: 'right',
                        verticalAlign: 'middle',
                        borderWidth: 0
                    },
                    series: settings.series
                });
            });

        }
    };

})(jQuery);
