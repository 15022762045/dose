//....ooo00000ooo........ooo00000ooo........ooo00000ooo........ooo00000ooo......

//�������й������û�����ӿ�


#include "G4UImanager.hh"
#include "G4RunManagerFactory.hh"
//���������
#include "Randomize.hh"

//���ӻ�
#include "ActionInitialization.hh"

//�����Ҫ��ͷ�ļ�
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"
//....ooo00000ooo........ooo00000ooo........ooo00000ooo........ooo00000ooo......
#include "G4SteppingVerbose.hh"
#include "G4GeometrySampler.hh"
#include "G4IStore.hh"
#include "G4ImportanceBiasing.hh"
#include "G4GeometryManager.hh"
int main(int argc,char** argv)
{


	G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
  G4long seed = time(0);
  G4Random::setTheEngine(new CLHEP::MTwistEngine(seed));
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default,10);

	auto detector = 
		new DetectorConstruction;
	runManager->SetUserInitialization(detector);
      G4GeometrySampler mgs(detector->GetWorldVolume(),"gamma");
    G4GeometrySampler mgs1(detector->GetWorldVolume(), "e-");
    G4GeometrySampler mgs2(detector->GetWorldVolume(), "e+");
	//ע����������
  G4VModularPhysicsList* physicsList = new FTFP_BERT();
	//G4VModularPhysicsList* physicsList = new Phy_List();
      physicsList->RegisterPhysics(new G4ImportanceBiasing(&mgs));
    physicsList->RegisterPhysics(new G4ImportanceBiasing(&mgs1));
    physicsList->RegisterPhysics(new G4ImportanceBiasing(&mgs2));
	runManager->SetUserInitialization(physicsList);

runManager->SetUserInitialization(new ActionInitialization());

	//����ΪGeant4��ǿ���࣬������Ҫ����
	//ע���û���ҹ�

	//��ʼ��G4����

  runManager->Initialize();
  detector->CreateImportanceStore();
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);    
  }
  else {  
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }
  G4GeometryManager::GetInstance()->OpenGeometry();
  // Job terminationS
  delete visManager;
  delete runManager;
  return 0;
}