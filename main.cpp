#include <napi.h>
#include <cups/cups.h>
#include <cups/ppd.h>


Napi::Value printFile(const Napi::CallbackInfo& info) {
    Napi::String filepath = info[0].ToString();
    
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    
    int jobId = cupsPrintFile("ipp_printer", filepath.Utf8Value().c_str(), filepath.Utf8Value().c_str(), 0, NULL);
    
    if (jobId == 0) {
        deferred.Reject(Napi::Number::New(info.Env(), cupsLastError()));
    } else {
        deferred.Resolve(Napi::Number::New(info.Env(), jobId));
    }
    
    return deferred.Promise();
}

Napi::Array getPrinters(const Napi::CallbackInfo& info) {
    
    cups_dest_t *dests;
    int num_dests = cupsGetDests(&dests);
    
    Napi::Array printersList = Napi::Array::New(info.Env(), num_dests);
    
    for (int i = 0; i < num_dests; i++) {
            ppd_file_t *ppd = ppdOpenFile(cupsGetPPD(dests[i].name));
            
            Napi::Object obj = Napi::Object::New(info.Env());
            obj.Set("name", Napi::String::New(info.Env(), dests[i].name));
            obj.Set("model", Napi::String::New(info.Env(), ppd->modelname));
            obj.Set("color", Napi::Boolean::New(info.Env(), ppd->color_device));
            obj.Set("default", Napi::Boolean::New(info.Env(), dests[i].is_default));
            
            ppdClose(ppd);
            printersList.Set(i, obj);
    }
    
    cupsFreeDests(num_dests, dests);
    return printersList;
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "printFile"), Napi::Function::New(env, printFile));
    exports.Set(Napi::String::New(env, "getPrinters"), Napi::Function::New(env, getPrinters));

    return exports;
};

NODE_API_MODULE(printer, init);
