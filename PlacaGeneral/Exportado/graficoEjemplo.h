
//static lv_obj_t * chart;
lv_chart_series_t * ser;

// Los valores iniciales del grafico se pasaron a variablesYlibrerias

static void slider_x_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    int32_t v = lv_slider_get_value(obj);
    lv_chart_set_zoom_x(ui_Chart3, v);
}

static void slider_y_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    int32_t v = lv_slider_get_value(obj);
    lv_chart_set_zoom_y(ui_Chart3, v);
}

/**
 * Display 1000 data points with zooming and scrolling.
 * See how the chart changes drawing mode (draw only vertical lines) when
 * the points get too crowded.
 */
void lv_example_chart_5(void)
{
    /*Create a chart*/
    /*
    chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, 200, 150);
    lv_obj_align(chart, LV_ALIGN_CENTER, -30, -30);
    */
    lv_chart_set_range(ui_Chart3, LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);
    

    /*Do not display points on the data*/
    lv_obj_set_style_size(ui_Chart3, 0, LV_PART_INDICATOR);

    //lv_chart_series_t * ser = lv_chart_add_series(ui_Chart3, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    ser = lv_chart_add_series(ui_Chart3, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    uint32_t pcnt = sizeof(ecg_sample) / sizeof(ecg_sample[0]);
    lv_chart_set_point_count(ui_Chart3, pcnt);
    lv_chart_set_ext_y_array(ui_Chart3, ser, (lv_coord_t *)ecg_sample);

    lv_obj_t * slider;
    slider = lv_slider_create(ui_Graficas);
    lv_slider_set_range(slider, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 10);
    lv_obj_add_event_cb(slider, slider_x_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(slider, 200, 10);
    lv_obj_align_to(slider, ui_Chart3, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    slider = lv_slider_create(ui_Graficas);
    lv_slider_set_range(slider, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 10);
    lv_obj_add_event_cb(slider, slider_y_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_size(slider, 10, 150);
    lv_obj_align_to(slider, ui_Chart3, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
}
