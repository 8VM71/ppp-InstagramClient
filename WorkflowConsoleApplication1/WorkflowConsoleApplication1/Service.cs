using System;
using System.Net.Http;
using System.Net.Http.Headers;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace WorkflowConsoleApplication1
{
    public class Service
    {
        private readonly string _basicsUrl = "http://localhost:5000/api/user/{0}/info";

        private readonly string _calculationsUrl = "http://localhost:5001/api/calculate/";

        public JObject GetUserInfo(string id)
        {
            var url = String.Format(_basicsUrl, id);
            using (var client = new HttpClient())
            {
                client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
                HttpResponseMessage response = client.GetAsync(url).Result;
                string content = response.Content.ReadAsStringAsync().Result;
                return content.Length > 0 ? JObject.Parse(content) : null;
            }
        }

        public string CalculateRate(dynamic json, string koef1, string koef2)
        {
            using (var client = new HttpClient())
            {
                json.factors = JObject.FromObject(new
                {
                    photo = Convert.ToDouble(koef1),
                    post = Convert.ToDouble(koef2)
                });

                var url = _calculationsUrl + json.ToString();
                client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
                var response = client.GetAsync(url).Result;
                string content = response.Content.ReadAsStringAsync().Result;
                try
                {
                    dynamic jsonObject = JObject.Parse(content);
                    return jsonObject.result.ToString();
                }
                catch (JsonReaderException ex)
                {
                    Console.WriteLine(ex.ToString());
                    return null;
                }
            }
        }

    }
}