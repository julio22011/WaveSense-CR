
// configuracion del altavos bluetooth:
static const i2s_config_t i2s_config = {
  .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN), // I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN
  .sample_rate = 44100, // corrected by info from bluetooth
  .bits_per_sample = (i2s_bits_per_sample_t) 16, // the DAC module will only take the 8bits from MSB  //////
  .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
  .communication_format = I2S_COMM_FORMAT_I2S_MSB,
  .intr_alloc_flags = 0, // default interrupt priority
  .dma_buf_count = 8, // 8
  .dma_buf_len = 32,  //64
  .use_apll = false
};
  
  // Para establecer una configuracion de los pines i2s:
i2s_pin_config_t my_pin_config = {
  .bck_io_num = BCLK_Ampl,
  .ws_io_num = LRC_Ampl,
  .data_out_num = DIN_Ampl,
  .data_in_num = I2S_PIN_NO_CHANGE
};


//a2dp_sink.set_pin_config(my_pin_config); // Establece los pines para que sea los indicados arriba
//////////////////////////////////

BluetoothA2DPSink a2dp_sink;

// Esta tarea habilita un altavos bluetooth
void tareaAudBlue(void * parameter){
  activarAudBlue = !activarAudBlue;

  //Lo siguiente configura el audio dependiendo de si se quiere o no usar el DAC interno:
  if (conDACinterno){
    //a2dp_sink.set_pin_config(my_pin_config);
    a2dp_sink.set_i2s_config(i2s_config); 
  }
  else {
    //a2dp_sink.set_i2s_config(i2s_config);
    a2dp_sink.set_pin_config(my_pin_config);
  }

  a2dp_sink.start("BluetoothJulio");  // inicia la conexion de audio bluetooth
  Serial.println("Altavos bluetooth activado");
  while (activarAudBlue){
    vTaskDelay(1000 / portTICK_PERIOD_MS); // espera mientras el altavoz esta activo
  }
  Serial.println("Altavos  desactivado");
  vTaskDelay(100 / portTICK_PERIOD_MS);
  vTaskDelete(NULL);
  //~BluetoothA2DPSink a2dp_sink;
} // fin de la tarea


