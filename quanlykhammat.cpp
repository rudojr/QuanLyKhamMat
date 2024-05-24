#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>


using namespace std;
//============================================================================================================================================//
class Patient{
    public:
        std::string cccd;
        std::string name;
        int birthYear;
    
    Patient(const std::string& cccd, const std::string& name, int birthYear)
    :cccd(cccd), name(name),birthYear(birthYear){}

    void print() const {
        std::cout << "So CCCD: " << cccd << ", Ten: " << name << ", Nam sinh: " << birthYear << std::endl;
    }
};
void menu_patients(std::vector<Patient>& patients);
void displayPatients(const std::vector<Patient>& patients);
void addPatient(std::vector<Patient>& patients);
void editPatient(std::vector<Patient>& patients, const std::string& cccd);
void deletePatient(std::vector<Patient>& patients, const std::string& cccd);
void searchByCCCD(const std::vector<Patient>& patients, const std::string& cccd);
//============================================================================================================================================//
class Service{
    public:
        int serviceID;
        std::string serviceName;
        double servicePrice;

    Service(const int serviceID, const std::string& serviceName, const double servicePrice)
    :serviceID(serviceID), serviceName(serviceName), servicePrice(servicePrice){}

    void print() const{
        std::cout << "Ma dich vu: " << serviceID << ", Ten dich vu: " << serviceName << ", Gia dich vu: " << servicePrice << std::endl;
    }
};
void displayServices(const std::vector<Service>& services);
void addService(std::vector<Service>& services);
void editService(std::vector<Service>& services, int serviceID);
void deleteService(std::vector<Service>& services, int serviceID);
void searchServiceByID(const std::vector<Service>& services, int serviceID);

//============================================================================================================================================//
std::vector<Patient> readPatientsFromFile(const std::string& filename) {
    std::vector<Patient> patients;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cccd, name;
        int birthYear;

        std::getline(ss, cccd, ',');
        std::getline(ss, name, ',');
        ss >> birthYear;

        patients.emplace_back(cccd, name, birthYear);
    }

    return patients;
}
//============================================================================================================================================//
void displayPatients(const std::vector<Patient>& patients)
{
    cout <<"Danh sach benh nhan.\n";
    for (const auto& patient: patients)
    {
        patient.print();
    }
}
//============================================================================================================================================//
void editPatient(std::vector<Patient>& patients, const std::string& cccd);

void addPatient(std::vector<Patient>& patients) {
    std::string cccd, name;
    int birthYear;
    bool cccdExists = false;

    do {
        std::cout << "Nhap so CCCD: ";
        std::cin >> cccd;

        // Kiểm tra xem CCCD có trùng không
        cccdExists = false;
        for (const auto& patient : patients) {
            if (patient.cccd == cccd) {
                cccdExists = true;
                std::cout << "So CCCD da ton tai trong he thong?\n";
                std::cout << "Ban co muon chinh sua thong tin CCCD hay khong ?(y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    editPatient(patients, cccd);
                    return;
                } else {
                    std::cout << "Vui long kiem tra lai so CCCD.\n";
                }
                break;
            }
        }
    } while (cccdExists);

    // Nhập thông tin bệnh nhân mới
    std::cout << "Nhap ten benh nhan (Vi du: ThienHD): ";
    std::cin >> name;
    std::cout << "Nhap nam sinh: ";
    std::cin >> birthYear;
    patients.emplace_back(cccd, name, birthYear);
}
//============================================================================================================================================//
void editPatient(std::vector<Patient>& patients, const std::string& cccd) {
    for (auto& patient : patients) {
        if (patient.cccd == cccd) {
            std::cout << "Nhap ten benh nhan (Vi du: ThienHD): ";
            std::cin >> patient.name;
            std::cout << "Nhap nam sinh: ";
            std::cin >> patient.birthYear;
            std::cout << "Du lieu benh nhan da duoc cap nhat thanh cong!\n";
            return;
        }
    }
    std::cout << "Khong tim thay thong tin benh nhan voi so CCCD tren. VUi long kiem tra lai thong tin !!" << std::endl;
}

//============================================================================================================================================//
void deletePatient(std::vector<Patient>& patients, const std::string& cccd) {
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->cccd == cccd) {
            patients.erase(it);
            std::cout << "Da xoa benh nhan khoi co so du lieu.!\n";
            return;
        }
    }
    std::cout << "Khong tim thay thong tin benh nhan voi so CCCD tren. VUi long kiem tra lai thong tin !!" << std::endl;
}
//============================================================================================================================================//
void searchByCCCD(const std::vector<Patient>& patients, const std::string& cccd) {
    bool found = false;
    for (const auto& patient : patients) {
        if (patient.cccd == cccd) {
            patient.print();
            found = true;
            return;
        }
    }
    if (!found) {
        std::cout << "Benh nhan voi CCCD " << cccd << " khong co trong co so du lieu!" << std::endl;
    }
}
//============================================================================================================================================//
void savePatientsToFile(const std::string& filename, const std::vector<Patient>& patients) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Loi khi tao file " << filename << std::endl;
        return;
    }

    for (const auto& patient : patients) {
        file << patient.cccd << "," << patient.name << "," << patient.birthYear << std::endl;
    }
    file.close();
    std::cout << "Luu file thanh cong";
}
//============================================================================================================================================//
void menu_patients(std::vector<Patient>& patients)
{
    int choice;
    std::string cccd;
    std::string name;
    do
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Xem danh sach benh nhan\n";
        std::cout << "2. Them benh nhan moi\n";
        std::cout << "3. Chinh sua thong tin benh nhan\n";
        std::cout << "4. Xoa benh nhan khoi danh sach\n";
        std::cout << "5. Tim kiem benh nhan bang CCCD\n";
        std::cout << "6. Luu du lieu vao file txt\n";
        std::cout << "7. THoat chuong trinh\n";
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayPatients(patients);
                break;
            case 2:
                addPatient(patients);
                break;
            case 3:
                std::cout << "Nhap so CCCD de chinh sua: ";
                std::cin >> cccd;
                editPatient(patients, cccd);
                break;
            case 4:
                std::cout << "Nhap so CCCD muon xoa: ";
                std::cin >> cccd;
                deletePatient(patients, cccd);
                break;
            case 5:
                std::cout << "Nhap so CCCD de tim kiem: ";
                std::cin >> cccd;
                searchByCCCD(patients, cccd);
                break;
            case 6:
                savePatientsToFile("patient_data.txt", patients);
                break;
            case 7:
                std::cout << "Dang thoat chuong trinh...\n";
                break;
            default:
                std::cout << "Lua chon khong hop le. Xin vui long nhap lai thong tin.\n";
        }
    } while (choice != 8);
}
//============================================================================================================================================//
std::vector<Service> readServicesFromFile(const std::string& filename) {
    std::vector<Service> services;
    std::ifstream file(filename);
    std::string line;
    services.clear();
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int serviceID;
        std::string serviceName;
        double servicePrice;

        std::getline(ss, line, ',');
        serviceID = std::stoi(line);

        std::getline(ss, serviceName, ',');

        ss >> servicePrice;

        services.emplace_back(serviceID, serviceName, servicePrice);
    }

    return services;
}
//============================================================================================================================================//
void displayServices(const std::vector<Service>& services) {
    for (const auto& service : services) {
        std::cout << "Ma DV: " << service.serviceID 
                  << ", Ten DV: " << service.serviceName 
                  << ", Gia ca: " << std::fixed << std::setprecision(0) << service.servicePrice << std::endl;
    }
}
//============================================================================================================================================//
void addService(std::vector<Service>& services) {
    int serviceID;
    std::string serviceName;
    double servicePrice;
    bool idExists;

    do {
        idExists = false;
        std::cout << "Nhap ma dich vu: ";
        std::cin >> serviceID;
        
        for (const auto& service : services) {
            if (service.serviceID == serviceID) {
                std::cout << "Ma dich vu da ton tai trong he thong. Vui long nhap ma moi.\n";
                idExists = true;
                break;
            }
        }
    } while (idExists);

    std::cout << "Nhap ten dich vu: ";
    std::cin.ignore();
    std::getline(std::cin, serviceName);
    std::cout << "Nhap gia ca: ";
    std::cin >> servicePrice;

    services.emplace_back(serviceID, serviceName, servicePrice);
}
//============================================================================================================================================//
void editService(std::vector<Service>& services, int serviceID) {
    for (auto& service : services) {
        if (service.serviceID == serviceID) {
            std::cout << "Nhap gia moi: ";
            std::cin >> service.servicePrice;
            std::cout << "Gia dich vu da duoc cap nhat thanh cong!\n";
            return;
        }
    }
    std::cout << "Khong tim thay ma dich vu!" << std::endl;
}
//============================================================================================================================================//
void deleteService(std::vector<Service>& services, int serviceID) {
    for (auto it = services.begin(); it != services.end(); ++it) {
        if (it->serviceID == serviceID) {
            services.erase(it);
            std::cout << "Dich vu co ma " << serviceID << " da duoc xoa khoi he thong!\n";
            return;
        }
    }
    std::cout << "Khong tim thay ma dich vu!" << std::endl;
}
//============================================================================================================================================//
void searchServiceByID(const std::vector<Service>& services, int serviceID) {
    for (const auto& service : services) {
        if (service.serviceID == serviceID) {
            service.print();
            return;
        }
    }
    std::cout << "Khong tim thay ma dich vu!" << std::endl;
}
//============================================================================================================================================//
void saveServicesToFile(const std::string& filename, const std::vector<Service>& services) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to create file " << filename << std::endl;
        return;
    }
    
    file << std::fixed << std::setprecision(0);

    for (const auto& service : services) {
        file << service.serviceID << "," << service.serviceName << "," << service.servicePrice << std::endl;
    }

    file.close();
    std::cout << "Luu file du lieu thanh cong";
}
//============================================================================================================================================//
void menu_services(std::vector<Service>& services) {
    int choice;
    int serviceID;
    std::string serviceName;

    do {
        std::cout << "\nService Menu:\n";
        std::cout << "1. Hien thi danh sach dich vu\n";
        std::cout << "2. Them dich vu moi\n";
        std::cout << "3. Sua gia thanh dich vu\n";
        std::cout << "4. Xoa dich vu\n";
        std::cout << "5. Tim kiem dich vu\n";
        std::cout << "6. Luu du lieu vao file txt\n";
        std::cout << "7. Thoat chuong trinh\n";
        std::cout << "Nhap lua chon: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayServices(services);
                break;
            case 2:
                addService(services);
                break;
            case 3:
                std::cout << "Nhap ma dich vu can sua: ";
                std::cin >> serviceID;
                editService(services, serviceID);
                break;
            case 4:
                std::cout << "Nhap ma dich vu can xoa: ";
                std::cin >> serviceID;
                deleteService(services, serviceID);
                break;
            case 5:
                std::cout << "Nhap ma dich vu can stim kiem: ";
                std::cin >> serviceID;
                searchServiceByID(services, serviceID);
                break;
            case 6:
                saveServicesToFile("services_new.txt", services);
                break;
            case 7:
                std::cout << "Dang thoat chuong trinh...\n";
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 6);
}
//============================================================================================================================================//
void generateInvoice(const std::vector<Patient>& patients, const std::vector<Service>& services) {
    std::string invoiceID;
    std::string patientID;
    std::vector<int> serviceIDs;

    // Nhập mã hóa đơn
    std::cout << "Nhap ma hoa don: ";
    std::cin >> invoiceID;

    // Nhập mã bệnh nhân và kiểm tra
    bool validPatient = false;
    while (!validPatient) {
        std::cout << "Nhap ma benh nhan: ";
        std::cin >> patientID;

        for (const auto& patient : patients) {
            if (patient.cccd == patientID) {
                validPatient = true;
                break;
            }
        }

        if (!validPatient) {
            std::cout << "Benh nhan khong ton tai. Vui long nhap lai." << std::endl;
        }
    }

    // Nhập mã dịch vụ
    int serviceID;
    std::cout << "Nhap ma dich vu (nhap 0 0 de ket thuc): ";
    while (std::cin >> serviceID && serviceID != 0) {
        serviceIDs.push_back(serviceID);
    }

    // In hóa đơn
    std::cout << "===============================" << std::endl;
    std::cout << "Hoa don: " << invoiceID << std::endl;
    std::cout << "Ten benh nhan: ";
    for (const auto& patient : patients) {
        if (patient.cccd == patientID) {
            std::cout << patient.name << std::endl;
            break;
        }
    }
    std::cout << "Dich vu:" << std::endl;
    double total = 0;
    for (int id : serviceIDs) {
        for (const auto& service : services) {
            if (service.serviceID == id) {
                std::cout << " - " << service.serviceName << ": " << service.servicePrice << std::endl;
                total += service.servicePrice;
                break;
            }
        }
    }
    std::cout << "Tong gia: " << total << std::endl;
    std::cout << "===============================" << std::endl;
}
//============================================================================================================================================//
int main()
{
    std::vector<Patient> patients;
    std::vector<Service> services;

    patients = readPatientsFromFile("patient_data.txt");
    services = readServicesFromFile("service_data.txt");

    int choice;

    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Quan ly benh nhan\n";
        std::cout << "2. Quan ly dich vu\n";
        std::cout << "3. Tao hoa don dich vu\n";
        std::cout << "4. Thoat chuogn trinh\n";
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                menu_patients(patients);
                break;
            case 2:
                menu_services(services);
                break;
            case 3:
                generateInvoice(patients, services);
                break;
            case 4:
                std::cout << "Dang thoat chuong trinh...\n";
                break;
            default:
                std::cout << "Lua chon khongh hop le.\n";
        }
    } while (choice != 4);

    return 0;
}
//============================================================================================================================================//