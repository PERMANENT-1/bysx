#include "ui_UartAssist.h"

UI_UartAssist::UI_UartAssist(QWidget *parent) : QMainWindow(parent) {
	centralWidget = new QWidget(parent);

	layout = new QHBoxLayout(centralWidget);
	leftLayout = new QVBoxLayout(centralWidget);
	rightLayout = new QVBoxLayout(centralWidget);
	settings = new QGroupBox(tr("Settings"), centralWidget);
	settingsLayout = new QFormLayout(settings);
	receiverOptions = new QGroupBox(tr("Receiver Options"), centralWidget);
	receiverOptionsLayout = new QVBoxLayout(receiverOptions);
	receiverFormatLayout = new QHBoxLayout(receiverOptions);
	transmitterOptions = new QGroupBox(tr("Transmitter Options"), centralWidget);
	transmitterOptionsLayout = new QVBoxLayout(transmitterOptions);
	transmitterFormatLayout = new QHBoxLayout(transmitterOptions);
	transmitterAutoLayout = new QHBoxLayout(transmitterOptions);
	countBytes = new QGroupBox(tr("Count"), centralWidget);
	countBytesLayout = new QVBoxLayout(countBytes);
	countReceivedLayout = new QHBoxLayout(countBytes);
	countTransmittedLayout = new QHBoxLayout(countBytes);

	receiverArea = new QPlainTextEdit(centralWidget);
	transmitterArea = new QTabWidget(centralWidget);
	transmitOne = new QPlainTextEdit(transmitterArea);
	transmitMore = new QTableWidget(5, 6, transmitterArea);

	settingCOM = new QComboBox(settings);
	settingBaudRate = new QComboBox(settings);
	settingBaudRateValidator = new QRegExpValidator(QRegExp("\\d{1,10}"), settings);
	settingFlowCtrl = new QComboBox(settings);
	settingDataBits = new QComboBox(settings);
	settingStopBits = new QComboBox(settings);
	settingParity = new QComboBox(settings);
	uartRefresh = new QPushButton(tr("Refresh"), settings);
	uartOnOff = new QPushButton(tr("Turn On"), settings);

	receiverAscii = new QRadioButton(tr("ASCII", "receiver"), receiverOptions);
	receiverHex = new QRadioButton(tr("Hex", "receiver"), receiverOptions);
	receiverShowTime = new QCheckBox(tr("Show Time"), receiverOptions);
	receiverClear = new QPushButton(tr("Clear"), receiverOptions);
	receiverSave = new QPushButton(tr("Save"), receiverOptions);

	transmitterAscii = new QRadioButton(tr("ASCII", "transmitter"), transmitterOptions);
	transmitterHex = new QRadioButton(tr("Hex", "transmitter"), transmitterOptions);
	transmitterNewLine = new QCheckBox(tr("Append \"\\r\\n\""), transmitterOptions);
	transmitterAuto = new QCheckBox(tr("Auto"), transmitterOptions);
	transmitterEvery = new QLabel(tr("every"), transmitterOptions);
	transmitterPeriod = new QLineEdit(transmitterOptions);
	transmitterPeriodValidator = new QRegExpValidator(QRegExp("\\d{1,4}"), transmitterOptions);
	transmitterMs = new QLabel(tr("ms"), transmitterOptions);
	transmitterTransmit = new QPushButton(tr("Transmit"), transmitterOptions);

	receivedBytes = new QLabel(tr("Received: ") + "0" + tr("B"), countBytes);
	resetReceived = new QPushButton(tr("Reset"), countBytes);
	transmittedBytes = new QLabel(tr("Transmitted: ") + "0" + tr("B"), countBytes);
	resetTransmitted = new QPushButton(tr("Reset"), countBytes);
	resetBoth = new QPushButton(tr("Reset Both"), countBytes);
}

UI_UartAssist::~UI_UartAssist(void) {
	centralWidget->deleteLater();

	layout->deleteLater();
	leftLayout->deleteLater();
	rightLayout->deleteLater();
	settings->deleteLater();
	settingsLayout->deleteLater();
	receiverOptions->deleteLater();
	receiverOptionsLayout->deleteLater();
	receiverFormatLayout->deleteLater();
	transmitterOptions->deleteLater();
	transmitterOptionsLayout->deleteLater();
	transmitterFormatLayout->deleteLater();
	transmitterAutoLayout->deleteLater();
	countBytes->deleteLater();
	countBytesLayout->deleteLater();
	countReceivedLayout->deleteLater();
	countTransmittedLayout->deleteLater();

	receiverArea->deleteLater();
	transmitterArea->deleteLater();
	transmitOne->deleteLater();
	for (int row = 0; row < transmitMore->rowCount(); ++row)
		for (int col = 0; col < transmitMore->columnCount(); ++col)
			transmitMore->cellWidget(row, col)->deleteLater();
	transmitMore->deleteLater();

	settingCOM->deleteLater();
	settingBaudRate->deleteLater();
	settingBaudRateValidator->deleteLater();
	settingFlowCtrl->deleteLater();
	settingDataBits->deleteLater();
	settingStopBits->deleteLater();
	settingParity->deleteLater();
	uartRefresh->deleteLater();
	uartOnOff->deleteLater();

	receiverAscii->deleteLater();
	receiverHex->deleteLater();
	receiverShowTime->deleteLater();
	receiverClear->deleteLater();
	receiverSave->deleteLater();

	transmitterAscii->deleteLater();
	transmitterHex->deleteLater();
	transmitterNewLine->deleteLater();
	transmitterAuto->deleteLater();
	transmitterEvery->deleteLater();
	transmitterPeriod->deleteLater();
	transmitterPeriodValidator->deleteLater();
	transmitterMs->deleteLater();
	transmitterTransmit->deleteLater();

	receivedBytes->deleteLater();
	resetReceived->deleteLater();
	transmittedBytes->deleteLater();
	resetTransmitted->deleteLater();
	resetBoth->deleteLater();
}

void UI_UartAssist::InitUI(QMainWindow *mainWindow) {
	InitLayout(mainWindow); // ��ʼ������
	InitStyle(mainWindow); // ��ʼ����ʽ
}

void UI_UartAssist::InitLayout(QMainWindow *mainWindow) {
	/* ������ */
	mainWindow->setWindowIcon(QIcon(":/UartAssist.ico")); // ͼ��
	mainWindow->setWindowTitle(tr("Uart Assist")); // ����

	/* ���� */
	mainWindow->setCentralWidget(centralWidget);

	centralWidget->setLayout(layout); // ���岼��
	layout->addLayout(leftLayout); // ��벿�ֲ���
	layout->addLayout(rightLayout); // �Ұ벿�ֲ���
	layout->setStretchFactor(leftLayout, 4); // ��벿��ռ80%
	layout->setStretchFactor(rightLayout, 1); // �Ұ벿��ռ20%

	rightLayout->addWidget(settings); // ��������
	settings->setLayout(settingsLayout);

	rightLayout->addWidget(receiverOptions); // ����ѡ��
	receiverOptions->setLayout(receiverOptionsLayout);

	rightLayout->addWidget(transmitterOptions); // ����ѡ��
	transmitterOptions->setLayout(transmitterOptionsLayout);

	rightLayout->addWidget(countBytes); // ������
	countBytes->setLayout(countBytesLayout);

	/* ������ */
	leftLayout->addWidget(receiverArea);
	leftLayout->setStretchFactor(receiverArea, 7); // ������ռ70%
	receiverArea->setReadOnly(true); // ����Ϊֻ��
	receiverArea->setCenterOnScroll(true); // �Զ�����ʹ�����ʾ������

	/* ������ */
	leftLayout->addWidget(transmitterArea);
	leftLayout->setStretchFactor(transmitterArea, 3); // ������ռ30%
	transmitterArea->addTab(transmitOne, tr("Transmit One")); // ��������
	transmitterArea->addTab(transmitMore, tr("Transmit More")); // ��������
	transmitterArea->setTabPosition(QTabWidget::West); // ��ǩ�������
	transmitterArea->setUsesScrollButtons(false); // ��ʹ�ù�����ť

	/* �������� */
	transmitMore->horizontalHeader()->setVisible(false); // �����б���
	transmitMore->verticalHeader()->setVisible(false); // �����б���
	transmitMore->setFrameShape(QFrame::NoFrame); // ������߿�
	transmitMore->setShowGrid(false); // ���ص�Ԫ��߿�
	transmitMore->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // ����Ӧ�п�
	transmitMore->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // �����1��
	transmitMore->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch); // �����4��
	transmitMore->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); // �����и�
	transmitMore->setEditTriggers(QAbstractItemView::NoEditTriggers); // ������༭
	transmitMore->setSelectionMode(QAbstractItemView::NoSelection); // ������ѡ��
	for (int row = 0; row < transmitMore->rowCount(); ++row)
		for (int col = 0; col < transmitMore->columnCount(); ++col)
			switch (col % 3) {
			case 0: transmitMore->setCellWidget(row, col, new QCheckBox(QString::number(row * 2 + col / 3), transmitMore)); break;
			case 1: transmitMore->setCellWidget(row, col, new QLineEdit("", transmitMore)); break;
			case 2: transmitMore->setCellWidget(row, col, new QPushButton(tr("Transmit"), transmitMore)); break;
			}

	/* �������� */
	settingsLayout->addRow(tr("COM"), settingCOM); // ����ѡ��
	settingsLayout->addRow(tr("Baud Rate"), settingBaudRate); // ������
	settingBaudRate->setEditable(true); // �����ʿɱ༭
	settingBaudRate->setValidator(settingBaudRateValidator); // ֻ������1��10λ����
	settingsLayout->addRow(tr("Flow Control"), settingFlowCtrl); // ������
	settingsLayout->addRow(tr("Data Bits"), settingDataBits); // ����λ
	settingsLayout->addRow(tr("Stop Bits"), settingStopBits); // ֹͣλ
	settingsLayout->addRow(tr("Parity"), settingParity); // ��żУ��
	settingsLayout->addRow(uartOnOff); // �򿪻�رմ���
	settingsLayout->addRow(uartRefresh); // ˢ�´���

	/* ����ѡ�� */
	receiverOptionsLayout->addLayout(receiverFormatLayout);
	receiverFormatLayout->addWidget(receiverAscii); // ASCII��ʾ
	receiverAscii->setChecked(true); // Ĭ��ѡ��ASCII
	receiverFormatLayout->addWidget(receiverHex); // 16������ʾ
	receiverOptionsLayout->addWidget(receiverShowTime); // ��ʾʱ��
	receiverOptionsLayout->addWidget(receiverClear); // ����
	receiverOptionsLayout->addWidget(receiverSave); // ����

	/* ����ѡ�� */
	transmitterOptionsLayout->addLayout(transmitterFormatLayout);
	transmitterFormatLayout->addWidget(transmitterAscii); // ASCII����
	transmitterAscii->setChecked(true); // Ĭ��ѡ��ASCII
	transmitterFormatLayout->addWidget(transmitterHex); // 16���Ʒ���
	transmitterOptionsLayout->addWidget(transmitterNewLine); // �Զ�����
	transmitterNewLine->setChecked(true); // Ĭ���Զ�����
	transmitterOptionsLayout->addLayout(transmitterAutoLayout);
	transmitterAutoLayout->addWidget(transmitterAuto); // ��ʱ����
	transmitterAutoLayout->addStretch(); // ���Ӽ��
	transmitterAutoLayout->addWidget(transmitterEvery); // ÿ��
	transmitterAutoLayout->addWidget(transmitterPeriod); // ����
	transmitterPeriod->setText("1000"); // Ĭ������1000����
	transmitterPeriod->setAlignment(Qt::AlignCenter); // ������ʾ
	transmitterPeriod->setValidator(transmitterPeriodValidator); // ֻ������1��4λ����
	transmitterAutoLayout->addWidget(transmitterMs); // ����
	transmitterOptionsLayout->addWidget(transmitterTransmit); // ����

	/* ������ */
	countBytesLayout->addLayout(countReceivedLayout);
	countReceivedLayout->addWidget(receivedBytes); // �յ��ֽ���
	countReceivedLayout->addWidget(resetReceived); // �յ��ֽ�����λ
	countBytesLayout->addLayout(countTransmittedLayout);
	countTransmittedLayout->addWidget(transmittedBytes); // �����ֽ���
	countTransmittedLayout->addWidget(resetTransmitted); // �����ֽ�����λ
	countBytesLayout->addWidget(resetBoth); // ȫ����λ
}

void UI_UartAssist::InitStyle(QMainWindow *mainWindow) {
	desktop = QApplication::desktop();
	mainWindow->setMinimumHeight(desktop->availableGeometry().height() * 0.9); // �߶�
	mainWindow->setMinimumWidth(desktop->availableGeometry().width() * 0.7); // ���

	receiverArea->setObjectName("receiverArea");
	transmitterArea->setObjectName("transmitterArea");
	transmitOne->setObjectName("transmitOne");
	transmitMore->setObjectName("transmitMore");
	settings->setObjectName("settings");
	receiverOptions->setObjectName("receiverOptions");
	transmitterOptions->setObjectName("transmitterOptions");
	countBytes->setObjectName("countBytes");

	QFile qssFile(":/UartAssist.qss");
	if (qssFile.open(QFile::ReadOnly)) {
		QString qss = QString::fromLatin1(qssFile.readAll());
		mainWindow->setStyleSheet(qss);
		qssFile.close();
	}
}
